
#include "MarkerInfo.h"

using ADTFStream::Extensions::MarkerInfo;

MarkerInfo::MarkerInfo(FILE* file, unsigned long long dataSize)
{
	markers = new char[dataSize];
	fread(markers, dataSize, 1, file);
}

MarkerInfo::~MarkerInfo()
{
	delete[] markers;
}
