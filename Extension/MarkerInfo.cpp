
#include "MarkerInfo.h"

MarkerInfo::MarkerInfo(FILE* file, unsigned long dataSize)
{
	markers = new char[dataSize];
	fread(markers, dataSize, 1, file);
}

MarkerInfo::~MarkerInfo()
{
	delete[] markers;
}
