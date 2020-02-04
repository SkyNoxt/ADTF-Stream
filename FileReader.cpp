
#include "FileReader.h"

void FileReader::start(std::function<void(const Block*)> callback)
{
	finished = false;
	producer = std::thread(&FileReader::produce, this);
	consumer = std::thread(&FileReader::consume, this, callback);
}

void FileReader::stop()
{
	finished = true;

	producer.join();
	consumer.join();
}

FileReader::FileReader(const char* file)
	: file(new File(file))
{
}

FileReader::FileReader(File* file)
	: file(file)
{
}

FileReader::~FileReader()
{
	stop();
	delete file;
}

void FileReader::produce()
{
	while (file->tell() < file->index.data->fileReferenceCount && !finished)
	{
		{
			std::lock_guard<std::mutex> lock(mutex);
			queue.push(file->read());
		}
		condition.notify_all();
	}
	{
		std::lock_guard<std::mutex> lock(mutex);
		finished = true;
	}
	condition.notify_all();
}

void FileReader::consume(std::function<void(const Block*)> callback)
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(mutex);
		condition.wait(lock, [this] { return this->finished || !this->queue.empty(); });
		while (!queue.empty())
		{
			callback(queue.front());
			delete queue.front();
			queue.pop();
		}
		if (finished)
			break;
	}
}
