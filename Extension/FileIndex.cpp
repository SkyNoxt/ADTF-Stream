
#include "FileIndex.h"

FileIndex::FileIndex(FILE* file, unsigned long dataSize)
{
	fileReferenceCount = dataSize / sizeof(FileIndexReference);
	fileReferences = new FileIndexReference[fileReferenceCount];
	fread(fileReferences, sizeof(FileIndexReference), fileReferenceCount, file);
}

FileIndex::~FileIndex()
{
	delete fileReferences;
}
