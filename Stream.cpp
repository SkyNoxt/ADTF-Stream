
#include "Stream.h"

namespace ADTFStream
{
	Stream::~Stream()
	{
		delete index;
		delete indexAdd;
	}
}
