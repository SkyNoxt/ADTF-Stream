
#include "IndexAdd.h"

IndexAdd::IndexAdd(FILE* file, unsigned long dataSize)
{
	fread(this, sizeof(IndexAdd), 1, file);
}
