
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
			char description[1912];

			// Constructors
			Header() = default;
			Header(FILE* file);
		};

#pragma pack(pop)

		// Member variables
		Header header;

		Extension<GUID> guid;
		Extension<FileIndex> index;
		Extension<IndexAdd> indexAdd;
		Extension<MarkerInfo> markerInfo;
		Extension<ReferencedFiles> referencedFiles;

		unsigned short streamCount = 0;
		Stream* streams = nullptr;

		// Member functions
		Block* read();
		unsigned long tell();
		void seek(unsigned long position = 0);

		// Constructor
		File(const char* filePath);

		// Destructor
		~File();

	  private:
		// Member variables
		std::mutex mutex;
		FILE* file = nullptr;
		unsigned long entry = 0;
		Extensions::Header* extensions = nullptr;
	};
}
