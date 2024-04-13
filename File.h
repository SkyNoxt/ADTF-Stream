
#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "Extensions/FileIndex.h"
#include "Extensions/GUID.h"
#include "Extensions/MarkerInfo.h"
#include "Extensions/ReferencedFiles.h"

#include "Block.h"
#include "Stream.h"

namespace ADTFStream
{
	using Extensions::FileIndex;
	using Extensions::GUID;
	using Extensions::MarkerInfo;
	using Extensions::ReferencedFiles;

	class File
	{
	  public:
#pragma pack(push, 1)

		// Inner class
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
			unsigned char reserved[30] = {};
			char description[1912] = {};

			// Constructors
			Header() = default;
			Header(FILE* file);
		};

#pragma pack(pop)

		// Inner class
		class Reader
		{
		  public:
			// Member variable
			File* file = nullptr;

			// Constructors
			Reader(const char* file);
			Reader(File* file);

			// Member functions
			void start(std::function<void(const Block*)> blockCallback = nullptr, std::function<void()> finishCallback = nullptr);
			void stop(bool finish);

			// Destructor
			~Reader();

		  private:
			// Member variables
			std::mutex mutex = {};
			std::condition_variable condition = {};
			std::queue<Block*> queue = {};

			std::thread producer = {};
			std::thread consumer = {};

			bool finished = true;

			// Member functions
			void produce();
			void consume(std::function<void(const Block*)> blockCallback, std::function<void()> finishCallback);
		};

		// Member variables
		Header header = {};

		Extension<GUID> guid = {};
		Extension<FileIndex> index = {};
		Extension<IndexAdd> indexAdd = {};
		Extension<MarkerInfo> markerInfo = {};
		Extension<ReferencedFiles> referencedFiles = {};

		unsigned short streamCount = 0;
		Stream* streams = nullptr;

		// Constructor
		File(const char* filePath);

		// Member functions
		Block* read();
		unsigned long long tell();
		FileIndex::Entry* seek(unsigned long long position = 0);

		// Destructor
		~File();

	  private:
		// Member variables
		FILE* file = nullptr;
		unsigned long long block = 0;
		Extensions::Header* extensions = nullptr;
	};
}
