#include "BMPReader.h"
#include <fstream>
#include <iostream>
#include "../../Debug/GDebug.h"
#include "../../Debug/TempProfiler.h"
#include "LImageOperations.h"

BMPReader::BMPReader()
{
}

ImageData* BMPReader::ReadFile(const char * fileName)
{
	TempProfiler("BMP Reader");
	ImageData* returnData = new ImageData();
	returnData->fileType = EImageFileType::BMP;

	char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	uint16_t bitsPerPixel;

	ifstream bmpStream(fileName);
	if (bmpStream.fail())
	{
		GDebug::LogError("BMP File " + (std::string)fileName + " could not be loaded");
		return 0;
	}

	bmpStream.read(header, 54);
	if (header[0] != 'B' || header[1] != 'M')
	{
		GDebug::LogError((std::string)fileName + " is not a correct BMP file");
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

	returnData->data = new char[imageSize];
	bmpStream.read(returnData->data, imageSize);
	bmpStream.close();

	return returnData;
}
