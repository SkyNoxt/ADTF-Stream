
#include "Stream.h"

Stream::~Stream()
{
	delete index;
	delete indexAdd;
}
