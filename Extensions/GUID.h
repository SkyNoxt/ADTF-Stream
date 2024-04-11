
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
	class GUID
	{
	  public:
		// Member variable
		char* guid = nullptr;

		// Constructor
		GUID(FILE* file, unsigned long long dataSize);

		// Destructor
		~GUID();
	};
}
