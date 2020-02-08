
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
	class StreamIndex
	{
	  public:
#pragma pack(push, 1)

		class Header
		{
		  public:
			// Member variables
			unsigned long fileIndexEntryCount = 0;
			unsigned long firstTime = 0;
			unsigned long lastTime = 0;
			unsigned int dataSize = 0;
			char name[228];
		};

		class Descriptor
		{
		  public:
			// Member variables
			char sampleType[512];
			char mediaType[512];
			unsigned int majorType;
			unsigned int minorType;
			unsigned int flags;
		};

#pragma pack(pop)

		// Member variables
		Header header;
		Descriptor descriptor;
		unsigned int codecSize = 0;
		unsigned char* codec = nullptr;

		unsigned long entryCount = 0;
		unsigned int* entries = nullptr;

		// Constructor
		StreamIndex(FILE* file, unsigned long dataSize);

		// Destructor
		~StreamIndex();
	};
}