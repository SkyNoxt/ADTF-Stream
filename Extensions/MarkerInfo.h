
#pragma once

#include <cstdio>

namespace ADTFStream::Extensions
{
	class MarkerInfo
	{
	  public:
		// Member variables
		char* markers = nullptr;

		// Constructor
		MarkerInfo(FILE* file, unsigned long long dataSize);

		// Destructor
		~MarkerInfo();
	};
}
