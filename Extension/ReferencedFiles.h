
#pragma once

#include <cstdio>

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
