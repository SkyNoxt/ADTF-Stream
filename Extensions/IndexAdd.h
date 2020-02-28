
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
#pragma pack(push, 1)

	class IndexAdd
	{
	  public:
		// Member variables
		unsigned long long streamIndexOffset = 0;
		unsigned int streamTableIndexOffset = 0;
		unsigned char reserved[20];

		// Constructor
		IndexAdd(FILE* file, unsigned long long dataSize);
	};

#pragma pack(pop)
}
