
#include "IndexAdd.h"

using ADTFStream::Extensions::IndexAdd;

IndexAdd::IndexAdd(FILE* file, unsigned long long dataSize)
{
	fread(this, sizeof(IndexAdd), 1, file);
}
