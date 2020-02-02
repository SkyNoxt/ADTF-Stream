
#include "ExtensionHeader.h"

ExtensionHeader::ExtensionHeader(FILE* file)
{
	fread(this, sizeof(ExtensionHeader), 1, file);
}
