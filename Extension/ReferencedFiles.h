
#pragma once

#include <cstdio>

#pragma pack(push)
#pragma pack(1)

class ReferencedFiles
{
public:
	// Member variables
	char* previous = nullptr;
	char* next = nullptr;

	// Constructor
	ReferencedFiles(FILE* file, unsigned long dataSize);

	// Destructor
	~ReferencedFiles();

private:
	// Member variable
	char* data = nullptr;
};

#pragma pack(pop)
