
#include "IndexAdd.h"

using ADTFStream::IndexAdd;

IndexAdd::IndexAdd(FILE* file, unsigned long dataSize)
{
	fread(this, sizeof(IndexAdd), 1, file);
}
