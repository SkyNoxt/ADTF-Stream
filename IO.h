
#pragma once

#include <cstdio>

namespace ADTFStream
{
	class IO
	{
	  public:
		// Static functions
		static void open(FILE** stream, const char* name, const char* mode);
		static unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
		static void seek(FILE* stream, long long int offset, int origin);
		static unsigned long long tell(FILE* stream);
		static void close(FILE* stream);
	};
}
