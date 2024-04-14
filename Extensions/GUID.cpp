
#include "GUID.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

namespace ADTFStream::Extensions
{
	GUID::GUID(FILE* file, unsigned long long dataSize)
	{
		guid = new char[dataSize];
		IO::read(guid, dataSize, 1, file);
	}

	GUID::~GUID()
	{
		delete guid;
	}
}
