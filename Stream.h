
#pragma once

#include "Extensions/Extension.h"
#include "Extensions/IndexAdd.h"
#include "Extensions/StreamIndex.h"

namespace ADTFStream
{
	using Extensions::Extension;
	using Extensions::IndexAdd;
	using Extensions::StreamIndex;

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
