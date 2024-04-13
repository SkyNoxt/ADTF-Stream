
#include "Header.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
}

using ADTFStream::Extensions::Header;

Header::Header(FILE* file)
{
	IO::read(this, sizeof(Header), 1, file);
}
