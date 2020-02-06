
#pragma once

#include <cstdio>

namespace ADTFStream
{
#pragma pack(push, 1)

	class IndexAdd
	{
	  public:
		// Member variables
		unsigned long streamIndexOffset = 0;
		unsigned int streamTableIndexOffset = 0;
		unsigned char reserved[20];

		// Constructor
		IndexAdd(FILE* file, unsigned long dataSize);
	};

#pragma pack(pop)
}
