
#pragma once

#include <cstdio>
#include <mutex>

#include "Extensions/Extension.h"
#include "Extensions/FileIndex.h"
#include "Extensions/GUID.h"
#include "Extensions/IndexAdd.h"
#include "Extensions/MarkerInfo.h"
#include "Extensions/ReferencedFiles.h"

#include "Block.h"
#include "Stream.h"

namespace ADTFStream
{
	using Extensions::Extension;
	using Extensions::FileIndex;
	using Extensions::GUID;
	using Extensions::IndexAdd;
	using Extensions::MarkerInfo;
	using Extensions::ReferencedFiles;

	class File
	{
	  public:
#pragma pack(push, 1)

		class Header
		{
		  public:
			// Member variables
			unsigned int fileId = 0;
			unsigned int versionId = 0;
			unsigned int flags = 0;
			unsigned int extensionCount = 0;
			unsigned long long extensionOffset = 0;
			unsigned long long dataOffset = 0;
			unsigned long long dataSize = 0;
			unsigned long long blockCount = 0;
			unsigned long long maxBlockSize = 0;
			unsigned long long duration = 0;
			unsigned long long fileTime = 0;
			unsigned char headerByteOrder = 0;
			unsigned long long timeOffset = 0;
			unsigned char patchNumber = 0;
			unsigned long long firstBlockOffset = 0;
			unsigned long long continuousOffset = 0;
			unsigned long long ringBufferEndOffset = 0;
			unsigned char reserved[30] = { 0 };
			char description[1912] = { 0 };

			// Constructors
			Header() = default;
			Header(FILE* file);
		};

#pragma pack(pop)

		// Member variables
		Header header = { 0 };

		Extension<GUID> guid = {};
		Extension<FileIndex> index = {};
		Extension<IndexAdd> indexAdd = {};
		Extension<MarkerInfo> markerInfo = {};
		Extension<ReferencedFiles> referencedFiles = {};

		unsigned short streamCount = 0;
		Stream* streams = nullptr;

		// Member functions
		Block* read();
		unsigned long long tell();
		FileIndex::Entry* seek(unsigned long long position = 0);

		// Constructor
		File(const char* filePath);

		// Destructor
		~File();

	  private:
		// Member variables
		FILE* file = nullptr;
		std::mutex mutex = {};
		unsigned long long block = 0;
		Extensions::Header* extensions = nullptr;
	};
}
