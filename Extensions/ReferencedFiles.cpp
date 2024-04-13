
#include <cstring>

#include "ReferencedFiles.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

using ADTFStream::Extensions::ReferencedFiles;

ReferencedFiles::ReferencedFiles(FILE* file, unsigned long long dataSize)
{
	data = new char[dataSize];
	IO::read(data, dataSize, 1, file);
	previous = data;
	next = data + strlen(previous) + 1;
}

ReferencedFiles::~ReferencedFiles()
{
	delete[] data;
}
