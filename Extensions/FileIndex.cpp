
#include "FileIndex.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

using ADTFStream::Extensions::FileIndex;

FileIndex::FileIndex(FILE* file, unsigned long long dataSize)
{
	entryCount = dataSize / sizeof(Entry);
	entries = new Entry[entryCount];
	IO::read(entries, sizeof(Entry), entryCount, file);
}

FileIndex::~FileIndex()
{
	delete entries;
}
