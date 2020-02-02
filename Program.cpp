
#include "FileReader.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc != 2)
		return 0;

	FileReader reader(argv[1]);

	for (unsigned short i = 0; i < reader.file->streamCount; ++i)
		std::cout << reader.file->streams[i].index->data->name << std::endl;

	reader.start([](const Sample* sample) {});

	return 0;
}
