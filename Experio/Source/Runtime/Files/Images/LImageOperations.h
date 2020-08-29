#pragma once
#include "ImageReader.h"

class LImageOperations
{
public:
	static EImageEncoding EncodeBitsPerPixel(int bitsPerPixel);
	static EImageEncoding EncodeBytesPerPixel(int bytesPerPixel);

	static int BitsPerPixel(EImageEncoding encoding);
	static int BytesPerPixel(EImageEncoding encoding);
};