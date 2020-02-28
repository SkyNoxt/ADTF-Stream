
#include "GUID.h"

using ADTFStream::Extensions::GUID;

GUID::GUID(FILE* file, unsigned long long dataSize)
{
	guid = new char[dataSize];
	fread(guid, dataSize, 1, file);
}

GUID::~GUID()
{
	delete guid;
}
