
#include <iostream>

#include "FileReader.h"

int main(int argc, char** argv)
{
	if (argc != 2)
		return 0;

	FileReader reader(argv[1]);
	reader.start([](const Block* block) {});

	return 0;
}
