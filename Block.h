
#pragma once

#include <cstdio>

namespace ADTFStream
{
	class Block
	{
	  public:
#pragma pack(push, 1)

		class Header
		{
		  public:
			// Member variables
			unsigned long long timeStamp = 0;
			unsigned int fileIndexEntry = 0;
			unsigned int previousOffset = 0;
			unsigned int size = 0;
			unsigned short streamId = 0;
			unsigned short flags = 0;
			unsigned long long streamIndexEntry = 0;

			unsigned char sampleVersion = 0;
			unsigned int sampleSize = 0;
			unsigned long long sampleTimeStamp = 0;
			unsigned int sampleFlags = 0;
		};

#pragma pack(pop)

		// Member variables
		Header header;
		unsigned char* data = nullptr;

		// Constructor
		Block(FILE* file);

		// Destructor
		~Block();
	};
}
