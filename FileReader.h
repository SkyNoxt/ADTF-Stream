
#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "File.h"

namespace ADTFStream
{
	class FileReader
	{
	  public:
		// Member variables
		File* file = nullptr;

		// Member functions
		void start(std::function<void(const Block*)> blockCallback = nullptr, std::function<void()> finishCallback = nullptr);
		void stop(bool finish);

		// Constructors
		FileReader(const char* file);
		FileReader(File* file);

		// Destructor
		~FileReader();

	  private:
		// Member variables
		std::mutex mutex;
		std::condition_variable condition;
		std::queue<Block*> queue;

		std::thread producer;
		std::thread consumer;

		bool finished = true;

		// Member functions
		void produce();
		void consume(std::function<void(const Block*)> blockCallback, std::function<void()> finishCallback);
	};
}
