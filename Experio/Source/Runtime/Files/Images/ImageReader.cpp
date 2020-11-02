#include "ImageReader.h"
#include "BMPReader.h"
#include "TGAReader.h"
#include "../LFileOperations.h"
#include "../../Debug/Debug.h"
#include "../../Framework/AssetMap.h"

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

	Debug::LogError("Image File was not recognized");
	return nullptr;
}

ImageData * ImageReader::ReadFile(unsigned int assetIndex)
{
	std::string filepath;
	if (AssetMap::assetMap.SafeGet(assetIndex, filepath))
	{
		return ImageReader::ReadFile(filepath.c_str());
	}
	return nullptr;
}
