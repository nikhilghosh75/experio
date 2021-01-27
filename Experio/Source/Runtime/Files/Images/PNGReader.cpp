#include "PNGReader.h"
#include "../../../ThirdParty/Lodepng/Lodepng.h"
#include "../../Debug/Debug.h"

PNGReader::PNGReader()
{
}

ImageData * PNGReader::ReadFile(const char * fileName)
{
	unsigned char* rawImage = nullptr;
	unsigned char* image = nullptr;
	unsigned int width, height;
	size_t imageSize = 0;
	unsigned int error;

	error = lodepng_load_file(&rawImage, &imageSize, fileName);
	if (error)
	{
		Debug::LogError(lodepng::error_text(error));
	}

	error = lodepng_decode32(&image, &width, &height, rawImage, imageSize);
	if (error)
	{
		Debug::LogError(lodepng::error_text(error));
	}

	delete rawImage;

	ImageData* returnData = new ImageData();
	returnData->width = width;
	returnData->height = height;
	returnData->data = image;
	returnData->encoding = EImageEncoding::TruecolorAlpha;
	returnData->internalFormat = EImageInternalFormat::RGBA;

	return returnData;
}
