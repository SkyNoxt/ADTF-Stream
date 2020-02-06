
#include <cstring>

#include "ReferencedFiles.h"

using ADTFStream::ReferencedFiles;

ReferencedFiles::ReferencedFiles(FILE* file, unsigned long dataSize)
{
	data = new char[dataSize];
	fread(data, dataSize, 1, file);
	previous = data;
	next = data + strlen(previous) + 1;
}

ReferencedFiles::~ReferencedFiles()
{
	delete[] data;
}
