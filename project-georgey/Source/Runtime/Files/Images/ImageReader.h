#pragma once
#include "../FileReader.h"

enum EImageFileType : uint8_t
{
	BMP,
	PNG
};

enum EImageEncoding : uint8_t
{
	Unencoded = 0,
	Grayscale = 8,
	GrayscaleAlpha = 16,
	Truecolor = 24,
	TruecolorAlpha = 32
};

class ImageData : TFileData
{
public:
	unsigned int width;
	unsigned int height;
	char* data;

	EImageFileType fileType;
	EImageEncoding encoding;
};

class ImageReader : FileReader<ImageData>
{
public:
	ImageReader()
	{

	};
};