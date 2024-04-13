
#include <cstring>

#include "IO.h"
#include "File.h"

using ADTFStream::File;

File::Header::Header(FILE* file)
{
	IO::read(this, sizeof(Header), 1, file);
}

void File::Reader::start(std::function<void(const Block*)> blockCallback, std::function<void()> finishCallback)
{
	finished = false;
	producer = std::thread(&Reader::produce, this);
	consumer = std::thread(&Reader::consume, this, blockCallback, finishCallback);
}

void File::Reader::stop(bool finish)
{
	finished = finish;

	if(producer.joinable())
		producer.join();
	if(consumer.joinable())
		consumer.join();
}

File::Reader::Reader(const char* file)
	: file(new File(file))
{
}

File::Reader::Reader(File* file)
	: file(file)
{
}

File::Reader::~Reader()
{
	stop(true);
	delete file;
}

void File::Reader::produce()
{
	while(file->tell() < file->header.blockCount && !finished)
	{
		{
			std::lock_guard<std::mutex> lock(mutex);
			queue.push(file->read());
		}
		condition.notify_one();
	}
	{
		std::lock_guard<std::mutex> lock(mutex);
		finished = true;
	}
	condition.notify_one();
}

void File::Reader::consume(std::function<void(const Block*)> blockCallback, std::function<void()> finishCallback)
{
	while(true)
	{
		std::unique_lock<std::mutex> lock(mutex);
		condition.wait(lock, [this]
					   { return this->finished || !this->queue.empty(); });
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

ADTFStream::Block* File::read()
{
	Block* read = new Block(file);
	++block;
	return read;
}

unsigned long long File::tell()
{
	return block;
}

ADTFStream::Extensions::FileIndex::Entry* File::seek(unsigned long long position)
{
	FileIndex::Entry* seek = index.data->entries + index.data->entryCount * position / header.blockCount;
	block = seek->blockIndex;
	IO::seek(file, seek->blockOffset, SEEK_SET);
	return seek;
}

File::File(const char* filePath)
{
	IO::open(&file, filePath, "rb");
	header = Header(file);

	IO::seek(file, header.extensionOffset, SEEK_SET);
	extensions = new Extensions::Header[header.extensionCount];
	IO::read(extensions, sizeof(Extensions::Header), header.extensionCount, file);

	for(unsigned long long i = 0; i < header.extensionCount; ++i)
		if(extensions[i].streamId > streamCount)
			streamCount = extensions[i].streamId;

	streams = new Stream[streamCount];
	Stream* currentStream = streams;

	for(unsigned long long i = 0; i < header.extensionCount; ++i)
	{
		if(!strcmp("index_add0", (char*)extensions[i].identifier))
			new(&indexAdd) Extension<IndexAdd>(&extensions[i], file);
		else if(!strcmp("index0", (char*)extensions[i].identifier))
			new(&index) Extension<FileIndex>(&extensions[i], file);
		else if(!strncmp("index_add", (char*)extensions[i].identifier, strlen("index_add")))
			(currentStream++)->indexAdd = new Extension<IndexAdd>(&extensions[i], file);
		else if(!strncmp("index", (char*)extensions[i].identifier, strlen("index")))
			currentStream->index = new Extension<StreamIndex>(&extensions[i], file);
		else if(!strcmp("GUID", (char*)extensions[i].identifier))
			new(&guid) Extension<GUID>(&extensions[i], file);
		else if(!strcmp("marker_info", (char*)extensions[i].identifier))
			new(&markerInfo) Extension<MarkerInfo>(&extensions[i], file);
		else if(!strcmp("referencedfiles", (char*)extensions[i].identifier))
			new(&referencedFiles) Extension<ReferencedFiles>(&extensions[i], file);
	}

	IO::seek(file, header.firstBlockOffset, SEEK_SET);
}

File::~File()
{
	delete[] streams;
	delete[] extensions;

	IO::close(file);
}
