#include "LImageOperations.h"

EImageEncoding LImageOperations::EncodeBitsPerPixel(int bitsPerPixel)
{
	return (EImageEncoding)bitsPerPixel;
}

EImageEncoding LImageOperations::EncodeBytesPerPixel(int bytesPerPixel)
{
	return (EImageEncoding)bytesPerPixel;
}

int LImageOperations::BitsPerPixel(EImageEncoding encoding)
{
	return (int)encoding;
}

int LImageOperations::BytesPerPixel(EImageEncoding encoding)
{
	return ((int)encoding) / 8;
}
