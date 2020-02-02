
#pragma once

#include "ExtensionHeader.h"

template <class T>
class Extension
{
public:
	// Member variables
	ExtensionHeader* header = nullptr;
	T* data;

	// Constructors
	Extension() = default;
	Extension(ExtensionHeader* header, FILE* file)
		: header(header)
	{
		unsigned long offset = ftell(file);
		fseek(file, header->dataOffset, SEEK_SET);
		data = new T(file, header->dataSize);
		fseek(file, offset, SEEK_SET);
	}

	// Destructor
	~Extension()
	{
		delete data;
	}
};
