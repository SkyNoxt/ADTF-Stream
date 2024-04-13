
#include "StreamIndex.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

using ADTFStream::Extensions::StreamIndex;

StreamIndex::StreamIndex(FILE* file, unsigned long long dataSize)
{
	IO::read(&header, sizeof(Header) + sizeof(Descriptor), 1, file);

	codecSize = header.dataSize - sizeof(Descriptor);
	if(codecSize)
	{
		codec = new unsigned char[codecSize];
		IO::read(codec, codecSize, 1, file);
	}

	entryCount = (dataSize - (sizeof(Header) + sizeof(Descriptor) + codecSize)) / sizeof(unsigned int);
	entries = new unsigned int[entryCount];
	IO::read(entries, sizeof(unsigned int), entryCount, file);
}

StreamIndex::~StreamIndex()
{
	delete entries;
	delete codec;
}
