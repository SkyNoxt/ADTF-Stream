
#include "Sample.h"

Sample::Sample(FILE* file)
{
	fread(&header, sizeof(Header), 1, file);
	data = new unsigned char[header.size];
	fread(data, header.size - sizeof(Header), 1, file);

	unsigned long position = ftell(file) % 0x10;
	if (position)
		fseek(file, 0x10 - position, SEEK_CUR);
}

Sample::~Sample()
{
	delete data;
}
