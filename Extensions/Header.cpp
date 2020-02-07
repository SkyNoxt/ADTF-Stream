
#include "Header.h"

using ADTFStream::Extensions::Header;

Header::Header(FILE* file)
{
	fread(this, sizeof(Header), 1, file);
}
