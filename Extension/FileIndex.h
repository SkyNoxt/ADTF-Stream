
#pragma once

#include <cstdio>

namespace ADTFStream
{
	class FileIndex
	{
	  public:
#pragma pack(push, 1)

		class Entry
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
		unsigned long entryCount = 0;
		Entry* entries = nullptr;

		// Constructors
		FileIndex(FILE* file, unsigned long dataSize);

		// Destructor
		~FileIndex();
	};
}
