#pragma once
#include "../FileReader.h"

enum class EImageFileType : uint8_t
{
	BMP,
	PNG,
	TGA
};

enum class EImageEncoding : uint8_t
{
	Unencoded = 0,
	Grayscale = 8,
	GrayscaleAlpha = 16,
	Truecolor = 24,
	TruecolorAlpha = 32
};

class ImageData
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
	ImageReader() { };

	static ImageData* ReadFile(const char* filePath);

	static ImageData* ReadFile(unsigned int assetIndex);
};