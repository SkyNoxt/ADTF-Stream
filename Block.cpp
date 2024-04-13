
#include "Block.h"

namespace ADTFStream::IO
{
	unsigned long long read(void* buffer, unsigned long long size, unsigned long long count, FILE* stream);
	void seek(FILE* stream, long long int offset, int origin);
	unsigned long long tell(FILE* stream);
}

using ADTFStream::Block;

Block::Block(FILE* file)
{
	IO::read(&header, sizeof(Header), 1, file);
	data = new unsigned char[header.sampleSize];
	IO::read(data, header.sampleSize, 1, file);

	unsigned char position = (IO::tell(file) + 5) & 0x0f;
	position ? IO::seek(file, 0x10 - position + 5, SEEK_CUR) : IO::seek(file, 5, SEEK_CUR);
}

Block::~Block()
{
	delete data;
}
