
#include "IO.h"

using ADTFStream::IO;

void IO::open(FILE** stream, const char* name, const char* mode)
{
#if defined _CRT_FUNCTIONS_REQUIRED
	fopen_s(stream, name, mode);
#else
	*stream = std::fopen(name, mode);
#endif
}

unsigned long long IO::read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream)
{
	return std::fread(buffer, size, count, stream);
}

void IO::seek(FILE* stream, long long int offset, int origin)
{
#if defined _CRT_FUNCTIONS_REQUIRED
	_fseeki64(stream, offset, origin);
#else
	std::fseek(stream, offset, origin);
#endif
}

unsigned long long IO::tell(FILE* stream)
{
#if defined _CRT_FUNCTIONS_REQUIRED
	return _ftelli64(stream);
#else
	return std::ftell(stream);
#endif
}

void close(FILE* stream)
{
	std::fclose(stream);
}
