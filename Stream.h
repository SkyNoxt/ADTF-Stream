
#pragma once

#include "Extension/Extension.h"
#include "Extension/IndexAdd.h"
#include "Extension/StreamIndex.h"

namespace ADTFStream
{
	class Stream
	{
	  public:
		// Member variables
		Extension<StreamIndex>* index = nullptr;
		Extension<IndexAdd>* indexAdd = nullptr;

		// Destructor
		~Stream();
	};
}
