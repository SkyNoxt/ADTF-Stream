
#include "StreamIndex.h"

StreamIndex::StreamIndex(FILE* file, unsigned long dataSize)
{
	fread(this, 0x100, 1, file);

	infoData = new unsigned char[infoDataSize];
	fread(infoData, infoDataSize, 1, file);

	streamReferenceCount = (dataSize - 0x100 - infoDataSize) / sizeof(unsigned int);
	streamReferences = new unsigned int[streamReferenceCount];
	fread(streamReferences, sizeof(unsigned int), streamReferenceCount, file);
}

StreamIndex::~StreamIndex()
{
	delete streamReferences;
	delete infoData;
}
