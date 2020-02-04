
#include "Block.h"

Block::Block(FILE* file)
{
	fread(&header, sizeof(Header), 1, file);
	data = new unsigned char[header.sampleSize];
	fread(data, header.sampleSize, 1, file);

	unsigned char position = (ftell(file) + 5) & 0x0f;
	position ? fseek(file, 0x10 - position + 5, SEEK_CUR) : fseek(file, 5, SEEK_CUR);
}

Block::~Block()
{
	delete data;
}
