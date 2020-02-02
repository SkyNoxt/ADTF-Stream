
#include "FileReader.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
		return 0;

	FileReader reader(argv[1]);

	for (unsigned short i = 0; i < reader.file->streamCount; ++i)
		std::cout << reader.file->streams[i].index->data->name << std::endl;

	reader.start([](const Block* block) { std::cout << std::hex << (int)block->data[0] << std::endl; });

	std::this_thread::sleep_for(std::chrono::minutes(1));

	return 0;
}
