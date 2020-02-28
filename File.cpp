
#include <cstring>
#include <new>

#include "File.h"

using ADTFStream::File;

File::Header::Header(FILE* file)
{
	fread(this, sizeof(Header), 1, file);
}

ADTFStream::Block* File::read()
{
	std::lock_guard<std::mutex> lock(mutex);
	Block* block = new Block(file);
	entry = block->header.fileIndexEntry + 1;
	return block;
}

unsigned long long File::tell()
{
	return entry;
}

ADTFStream::Extensions::FileIndex::Entry* File::seek(unsigned long long position)
{
	std::lock_guard<std::mutex> lock(mutex);
	entry = position;
	FileIndex::Entry* seek = index.data->entries + entry;
	fseek(file, seek->blockOffset, SEEK_SET);
	return seek;
}

File::File(const char* filePath)
	: file(fopen(filePath, "rb"))
{
	header = Header(file);

	fseek(file, header.extensionOffset, SEEK_SET);
	extensions = new Extensions::Header[header.extensionCount];
	fread(extensions, sizeof(Extensions::Header), header.extensionCount, file);

	for (unsigned long long i = 0; i < header.extensionCount; ++i)
		if (extensions[i].streamId > streamCount)
			streamCount = extensions[i].streamId;

	streams = new Stream[streamCount];
	Stream* currentStream = streams;

	for (unsigned long long i = 0; i < header.extensionCount; ++i)
	{
		if (!strcmp("index_add0", (char*)extensions[i].identifier))
			new (&indexAdd) Extension<IndexAdd>(&extensions[i], file);
		else if (!strcmp("index0", (char*)extensions[i].identifier))
			new (&index) Extension<FileIndex>(&extensions[i], file);
		else if (!strncmp("index_add", (char*)extensions[i].identifier, strlen("index_add")))
			(currentStream++)->indexAdd = new Extension<IndexAdd>(&extensions[i], file);
		else if (!strncmp("index", (char*)extensions[i].identifier, strlen("index")))
			currentStream->index = new Extension<StreamIndex>(&extensions[i], file);
		else if (!strcmp("GUID", (char*)extensions[i].identifier))
			new (&guid) Extension<GUID>(&extensions[i], file);
		else if (!strcmp("marker_info", (char*)extensions[i].identifier))
			new (&markerInfo) Extension<MarkerInfo>(&extensions[i], file);
		else if (!strcmp("referencedfiles", (char*)extensions[i].identifier))
			new (&referencedFiles) Extension<ReferencedFiles>(&extensions[i], file);
	}

	fseek(file, header.firstBlockOffset, SEEK_SET);
}

File::~File()
{
	delete[] streams;
	delete[] extensions;

	fclose(file);
}
