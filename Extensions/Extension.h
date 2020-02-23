
#pragma once

#include "Header.h"

namespace ADTFStream::Extensions
{
	template <class T>
	class Extension
	{
	  public:
		// Member variables
		Header* header = nullptr;
		T* data = nullptr;

		// Constructors
		Extension() = default;
		Extension(Header* header, FILE* file)
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
}
