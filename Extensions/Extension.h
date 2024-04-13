
#pragma once

#include "Header.h"

namespace ADTFStream::IO
{
	void seek(FILE* stream, long long int offset, int origin);
	unsigned long long tell(FILE* stream);
}

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
			unsigned long long offset = IO::tell(file);
			IO::seek(file, header->dataOffset, SEEK_SET);
			data = new T(file, header->dataSize);
			IO::seek(file, offset, SEEK_SET);
		}

		// Destructor
		~Extension()
		{
			delete data;
		}
	};
}
