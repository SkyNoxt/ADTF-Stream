
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
	class FileIndex
	{
	  public:
#pragma pack(push, 1)

		// Inner class
		class Entry
		{
		  public:
			// Member variables
			unsigned long long timeStamp = 0;
			unsigned int size = 0;
			unsigned short streamId = 0;
			unsigned short flags = 0;
			unsigned long long blockOffset = 0;
			unsigned long long blockIndex = 0;
			unsigned long long streamIndex = 0;
			unsigned int streamIndexEntry = 0;
		};

#pragma pack(pop)

		// Member variables
		unsigned long long entryCount = 0;
		Entry* entries = nullptr;

		// Constructor
		FileIndex(FILE* file, unsigned long long dataSize);

		// Destructor
		~FileIndex();
	};
}
