
#pragma once

#include <cstdio>

class GUID
{
public:
	// Member variable
	char* guid = nullptr;

	// Constructors
	GUID(FILE* file, unsigned long dataSize);

	// Destructor
	~GUID();
};
