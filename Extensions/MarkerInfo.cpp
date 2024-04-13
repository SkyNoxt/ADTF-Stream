
#include "MarkerInfo.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

using ADTFStream::Extensions::MarkerInfo;

MarkerInfo::MarkerInfo(FILE* file, unsigned long long dataSize)
{
	markers = new char[dataSize];
	IO::read(markers, dataSize, 1, file);
}

MarkerInfo::~MarkerInfo()
{
	delete[] markers;
}
