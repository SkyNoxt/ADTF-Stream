
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
	class StreamIndex
	{
	  public:
#pragma pack(push, 1)

		// Inner class
		class Header
		{
		  public:
			// Member variables
			unsigned long long fileIndexEntryCount = 0;
			unsigned long long firstTime = 0;
			unsigned long long lastTime = 0;
			unsigned int dataSize = 0;
			char name[228] = {};
		};

		// Inner class
		class Descriptor
		{
		  public:
			// Member variables
			char sampleType[512] = {};
			char mediaType[512] = {};
			unsigned int majorType = 0;
			unsigned int minorType = 0;
			unsigned int flags = 0;
		};

#pragma pack(pop)

		// Member variables
		Header header = {};
		Descriptor descriptor = {};
		unsigned int codecSize = 0;
		unsigned char* codec = nullptr;

		unsigned long long entryCount = 0;
		unsigned int* entries = nullptr;

		// Constructor
		StreamIndex(FILE* file, unsigned long long dataSize);

		// Destructor
		~StreamIndex();
	};
}
