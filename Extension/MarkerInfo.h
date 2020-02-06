
#pragma once

#include <cstdio>

namespace ADTFStream
{
	class MarkerInfo
	{
	  public:
		// Member variables
		char* markers = nullptr;

		// Constructor
		MarkerInfo(FILE* file, unsigned long dataSize);

		// Destructor
		~MarkerInfo();
	};
}
