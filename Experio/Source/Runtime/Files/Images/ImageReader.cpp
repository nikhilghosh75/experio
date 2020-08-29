#include "ImageReader.h"
#include "BMPReader.h"
#include "TGAReader.h"
#include "../LFileOperations.h"
#include "../../Debug/GDebug.h"

ImageData * ImageReader::ReadFile(const char * fileName)
{
	std::string extension = LFileOperations::GetExtension(fileName);

	if (extension == "bmp")
	{
		BMPReader reader;
		return reader.ReadFile(fileName);
	}
	else if (extension == "tga")
	{
		TGAReader reader;
		return reader.ReadFile(fileName);
	}

	GDebug::LogError("Font File was not recognized");
	return nullptr;
}
