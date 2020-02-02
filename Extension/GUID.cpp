
#include "GUID.h"

GUID::GUID(FILE* file, unsigned long dataSize)
{
	guid = new char[dataSize];
	fread(guid, dataSize, 1, file);
}

GUID::~GUID()
{
	delete guid;
}
