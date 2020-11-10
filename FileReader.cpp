
#include "FileReader.h"

using ADTFStream::FileReader;

void FileReader::start(std::function<void(const Block*)> blockCallback, std::function<void()> finishCallback)
{
	finished = false;
	producer = std::thread(&FileReader::produce, this);
	consumer = std::thread(&FileReader::consume, this, blockCallback, finishCallback);
}

void FileReader::stop(bool finish)
{
	finished = finish;

	if(producer.joinable())
		producer.join();
	if(consumer.joinable())
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
	stop(true);
	delete file;
}

void FileReader::produce()
{
	while(file->tell() < file->index.data->entryCount && !finished)
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

void FileReader::consume(std::function<void(const Block*)> blockCallback, std::function<void()> finishCallback)
{
	while(true)
	{
		std::unique_lock<std::mutex> lock(mutex);
		condition.wait(lock, [this] { return this->finished || !this->queue.empty(); });
		while(!queue.empty())
		{
			if(blockCallback)
				blockCallback(queue.front());
			delete queue.front();
			queue.pop();
		}
		if(finished)
			break;
	}
	if(finishCallback)
		finishCallback();
}
