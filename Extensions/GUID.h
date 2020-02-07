
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
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
}
