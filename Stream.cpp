
#include "Stream.h"

using ADTFStream::Stream;

Stream::~Stream()
{
	delete index;
	delete indexAdd;
}
