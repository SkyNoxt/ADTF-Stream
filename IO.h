
#pragma once

#include <cstdio>

namespace ADTFStream::IO
{
	// Namespace functions
	void open(FILE** stream, const char* name, const char* mode);
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
	void seek(FILE* stream, long long int offset, int origin);
	unsigned long long tell(FILE* stream);
	void close(FILE* stream);
}
