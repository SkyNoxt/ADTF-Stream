
#include "ExtensionHeader.h"

using ADTFStream::ExtensionHeader;

ExtensionHeader::ExtensionHeader(FILE* file)
{
	fread(this, sizeof(ExtensionHeader), 1, file);
}
