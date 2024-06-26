
#include "IndexAdd.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

namespace ADTFStream::Extensions
{
	IndexAdd::IndexAdd(FILE* file, unsigned long long dataSize)
	{
		IO::read(this, sizeof(IndexAdd), 1, file);
	}
}
