
#include "StreamIndex.h"

using ADTFStream::Extensions::StreamIndex;

StreamIndex::StreamIndex(FILE* file, unsigned long long dataSize)
{
	fread(&header, sizeof(Header) + sizeof(Descriptor), 1, file);

	codecSize = header.dataSize - sizeof(Descriptor);
	if(codecSize)
	{
		codec = new unsigned char[codecSize];
		fread(codec, codecSize, 1, file);
	}

	entryCount = (dataSize - (sizeof(Header) + sizeof(Descriptor) + codecSize)) / sizeof(unsigned int);
	entries = new unsigned int[entryCount];
	fread(entries, sizeof(unsigned int), entryCount, file);
}

StreamIndex::~StreamIndex()
{
	delete entries;
	delete codec;
}
