
#include "FileIndex.h"

using ADTFStream::Extensions::FileIndex;

FileIndex::FileIndex(FILE* file, unsigned long dataSize)
{
	entryCount = dataSize / sizeof(Entry);
	entries = new Entry[entryCount];
	fread(entries, sizeof(Entry), entryCount, file);
}

FileIndex::~FileIndex()
{
	delete entries;
}
