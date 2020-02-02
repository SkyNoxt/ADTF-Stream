
#include "Block.h"

Block::Block(FILE* file)
{
	fread(&header, sizeof(Header), 1, file);
	data = new unsigned char[header.sampleSize];
	fread(data, header.sampleSize, 1, file);
	fseek(file, 5, SEEK_CUR);

	unsigned char position = ftell(file) % 0x10;
	if (position)
		fseek(file, 0x10 - position, SEEK_CUR);
}

Block::~Block()
{
	delete data;
}
