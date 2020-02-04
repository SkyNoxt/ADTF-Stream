
#include "File.h"

File::Header::Header(FILE* file)
{
	fread(this, sizeof(Header), 1, file);
}

Block* File::read()
{
	return new Block(file);
}

void File::seek(unsigned int entry)
{
	fseek(file, index.data->fileReferences[entry].blockOffset, SEEK_SET);
}

File::File(const char* filePath)
	: file(fopen(filePath, "rb"))
{
	header = Header(file);

	fseek(file, header.extensionOffset, SEEK_SET);
	extensions = new ExtensionHeader[header.extensionCount];
	fread(extensions, sizeof(ExtensionHeader), header.extensionCount, file);

	for (unsigned long i = 0; i < header.extensionCount; ++i)
		if (extensions[i].streamId > streamCount)
			streamCount = extensions[i].streamId;

	streams = new Stream[streamCount];
	Stream* currentStream = streams;

	for (unsigned long i = 0; i < header.extensionCount; ++i)
	{
		if (!strcmp("index_add0", (char*)extensions[i].identifier))
			new (&indexAdd) Extension<IndexAdd>(&extensions[i], file);
		else if (!strcmp("index0", (char*)extensions[i].identifier))
			new (&index) Extension<FileIndex>(&extensions[i], file);
		else if (!strncmp("index_add", (char*)extensions[i].identifier, strlen("index_add")))
			(currentStream++)->indexAdd = new Extension<IndexAdd>(&extensions[i], file);
		else if (!strncmp("index", (char*)extensions[i].identifier, strlen("index")))
			currentStream->index = new Extension<StreamIndex>(&extensions[i], file);
		else if (!strcmp("GUID", (char*)extensions[i].identifier))
			new (&guid) Extension<GUID>(&extensions[i], file);
		else if (!strcmp("marker_info", (char*)extensions[i].identifier))
			new (&markerInfo) Extension<MarkerInfo>(&extensions[i], file);
		else if (!strcmp("referencedfiles", (char*)extensions[i].identifier))
			new (&referencedFiles) Extension<ReferencedFiles>(&extensions[i], file);
	}

	fseek(file, header.firstBlockOffset, SEEK_SET);
}

File::~File()
{
	delete[] streams;

	delete extensions;
	fclose(file);
}
