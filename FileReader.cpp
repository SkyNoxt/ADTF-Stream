
#include "FileReader.h"

void FileReader::start(std::function<void(const Block*)> callback)
{
	finished = false;
	producer = new std::thread(&FileReader::produce, this);
	consumer = new std::thread(&FileReader::consume, this, callback);
}

void FileReader::stop()
{
	finished = true;

	producer->join();
	consumer->join();

	delete producer;
	delete consumer;
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
	for (unsigned long i = 0; i < file->header.blockCount; ++i)
	{
		{
			std::lock_guard<std::mutex> lock(mutex);
			queue.push(file->read());
		}
		condition.notify_all();
		if (finished)
			break;
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
