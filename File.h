
#pragma once

#include <cstdio>
#include <cstring>

#include <new>

#include "Extension/Extension.h"
#include "Extension/FileIndex.h"
#include "Extension/GUID.h"
#include "Extension/IndexAdd.h"
#include "Extension/ReferencedFiles.h"

#include "Sample.h"
#include "Stream.h"

class File
{
public:
#pragma pack(push)
#pragma pack(1)

	class FileHeader
	{
	public:
		// Member variables
		unsigned int fileId = 0;
		unsigned int versionId = 0;
		unsigned int flags = 0;
		unsigned int extensionCount = 0;
		unsigned long extensionOffset = 0;
		unsigned long dataOffset = 0;
		unsigned long dataSize = 0;
		unsigned long blockCount = 0;
		unsigned long maxBlockSize = 0;
		unsigned long duration = 0;
		unsigned long fileTime = 0;
		unsigned char headerByteOrder = 0;
		unsigned long timeOffset = 0;
		unsigned char patchNumber = 0;
		unsigned long firstBlockOffset = 0;
		unsigned long continuousOffset = 0;
		unsigned long ringBufferEndOffset = 0;
		unsigned char reserved[30];
		unsigned char description[1912];

		// Constructors
		FileHeader() = default;
		FileHeader(FILE* file);
	};

#pragma pack(pop)

	// Member variables
	FileHeader header;

	Extension<GUID> guid;
	Extension<FileIndex> index;
	Extension<IndexAdd> indexAdd;
	Extension<ReferencedFiles> referencedFiles;

	unsigned short streamCount = 0;
	Stream* streams = nullptr;

	// Member functions
	Sample* read();
	void seek(unsigned int entry);

	// Constructor
	File(const char* filePath);

	// Destructor
	~File();

private:
	// Member variables
	FILE* file = nullptr;
	ExtensionHeader* extensions = nullptr;
};
