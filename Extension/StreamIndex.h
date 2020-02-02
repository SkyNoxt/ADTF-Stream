
#pragma once

#include <cstdio>

#pragma pack(push)
#pragma pack(1)

class StreamIndex
{
public:
	// Member variables
	unsigned long entryCount = 0;
	unsigned long firstTime = 0;
	unsigned long lastTime = 0;
	unsigned int infoDataSize = 0;
	unsigned char name[228];

	unsigned char* infoData = nullptr;

	unsigned int streamReferenceCount = 0;
	unsigned int* streamReferences = nullptr;

	// Constructor
	StreamIndex(FILE* file, unsigned long dataSize);

	// Destructor
	~StreamIndex();
};

#pragma pack(pop)
