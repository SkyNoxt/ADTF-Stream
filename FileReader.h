
#pragma once

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "File.h"

class FileReader
{
public:
	// Member variables
	File* file = nullptr;

	// Member functions
	void start(std::function<void(const Sample*)> callback);
	void stop();

	// Constructors
	FileReader(const char* file);
	FileReader(File* file);

	// Destructor
	~FileReader();

private:
	// Member variables
	std::mutex mutex;
	std::condition_variable condition;
	std::queue<Sample*> queue;

	std::thread* producer = nullptr;
	std::thread* consumer = nullptr;

	bool finished = true;

	// Member functions
	void produce();
	void consume(std::function<void(const Sample*)> callback);
};
