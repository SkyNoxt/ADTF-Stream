
#pragma once

#include <cstdio>

class FileIndex
{
public:
#pragma pack(push)
#pragma pack(1)

	class FileIndexReference
	{
	public:
		// Member variables
		unsigned long timeStamp = 0;
		unsigned int size = 0;
		unsigned short streamId = 0;
		unsigned short flags = 0;
		unsigned long blockOffset = 0;
		unsigned long blockIndex = 0;
		unsigned long streamIndex = 0;
		unsigned int streamIndexEntry = 0;
	};

#pragma pack(pop)

	// Member variables
	unsigned long fileReferenceCount = 0;
	FileIndexReference* fileReferences = nullptr;

	// Constructors
	FileIndex(FILE* file, unsigned long dataSize);

	// Destructor
	~FileIndex();
};
