
#include "IO.h"

void ADTFStream::IO::open(FILE** stream, const char* name, const char* mode)
{
#if defined _CRT_FUNCTIONS_REQUIRED
	fopen_s(stream, name, mode);
#else
	*stream = fopen(name, mode);
#endif
}

unsigned long long ADTFStream::IO::read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream)
{
	return fread(buffer, size, count, stream);
}

void ADTFStream::IO::seek(FILE* stream, long long int offset, int origin)
{
#if defined _CRT_FUNCTIONS_REQUIRED
	_fseeki64(stream, offset, origin);
#else
	fseek(stream, offset, origin);
#endif
}

unsigned long long ADTFStream::IO::tell(FILE* stream)
{
#if defined _CRT_FUNCTIONS_REQUIRED
	return _ftelli64(stream);
#else
	return ftell(stream);
#endif
}

void ADTFStream::IO::close(FILE* stream)
{
	fclose(stream);
}
