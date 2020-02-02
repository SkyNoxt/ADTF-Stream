
#pragma once

#include <cstdio>

#pragma pack(push)
#pragma pack(1)

class ExtensionHeader
{
public:
	// Member variables
	unsigned char identifier[384];
	unsigned short streamId = 0;
	unsigned char reserved1[2];
	unsigned int userId = 0;
	unsigned int typeId = 0;
	unsigned int versionId = 0;
	unsigned long dataOffset = 0;
	unsigned long dataSize = 0;
	unsigned char reserved[96];

	// Constructors
	ExtensionHeader() = default;
	ExtensionHeader(FILE* file);
};

#pragma pack(pop)
