#pragma once
#include <stdint.h>

enum class EImageEncoding : uint8_t
{
	Unencoded = 0,
	Grayscale = 8,
	Alpha = 9, // Note that GL ALPHA is 8 bytes
	GrayscaleAlpha = 16,
	Truecolor = 24,
	TruecolorAlpha = 32
};

enum class EImageInternalFormat : uint8_t
{
	R,
	RG,
	RGB,
	BGR,
	RGBA,
	BGRA,
	A
};

enum class EImageCompressionType : uint8_t
{
	None,
	Deflate
};

class ImageData
{
public:
	unsigned int width;
	unsigned int height;
	unsigned char* data;
	EImageEncoding encoding;
	EImageInternalFormat internalFormat;
};

class ImageReader
{
public:
	ImageReader() { };

	static ImageData* ReadFile(const char* filePath);

	static ImageData* ReadFile(unsigned int assetIndex);
};