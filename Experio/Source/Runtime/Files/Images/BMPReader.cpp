#include "BMPReader.h"
#include <fstream>
#include <iostream>
#include "../../Debug/Debug.h"
#include "../../Debug/TempProfiler.h"
#include "LImageOperations.h"

BMPReader::BMPReader()
{
}

ImageData* BMPReader::ReadFile(const char * fileName)
{
	TempProfiler profiler("BMP Reader");
	ImageData* returnData = new ImageData();

	char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	uint16_t bitsPerPixel;

	std::ifstream bmpStream(fileName);
	if (bmpStream.fail())
	{
		Debug::LogError("BMP File " + (std::string)fileName + " could not be loaded");
		return 0;
	}

	bmpStream.read(header, 54);
	if (header[0] != 'B' || header[1] != 'M')
	{
		Debug::LogError((std::string)fileName + " is not a correct BMP file");
		return 0;
	}

	dataPos = *(int*)&(header[10]);
	imageSize = *(int*)&(header[34]);
	bitsPerPixel = *(uint16_t*)&(header[28]);
	returnData->width = *(int*)&(header[18]);
	returnData->height = *(int*)&(header[22]);

	if (imageSize == 0)
	{
		imageSize = returnData->width * returnData->height * 3;
	}
	if (dataPos == 0)
	{
		dataPos = 54;
	}

	returnData->encoding = LImageOperations::EncodeBitsPerPixel(bitsPerPixel);
	if (bitsPerPixel == 24)
		returnData->internalFormat = EImageInternalFormat::BGR;
	else
		returnData->internalFormat = EImageInternalFormat::BGRA;

	returnData->data = new unsigned char[imageSize];
	bmpStream.read(reinterpret_cast<char*>(returnData->data), imageSize);
	bmpStream.close();

	return returnData;
}
