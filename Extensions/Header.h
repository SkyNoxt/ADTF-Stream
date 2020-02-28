
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
#pragma pack(push, 1)

	class Header
	{
	  public:
		// Member variables
		char identifier[384];
		unsigned short streamId = 0;
		unsigned char reserved1[2];
		unsigned int userId = 0;
		unsigned int typeId = 0;
		unsigned int versionId = 0;
		unsigned long long dataOffset = 0;
		unsigned long long dataSize = 0;
		unsigned char reserved[96];

		// Constructors
		Header() = default;
		Header(FILE* file);
	};

#pragma pack(pop)
}
