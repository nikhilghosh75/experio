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

uint64_t LImageOperations::SizeOfImage(int width, int height, EImageEncoding encoding)
{
	return height * width * BytesPerPixel(encoding);
}

uint64_t LImageOperations::SizeOfImage(const ImageData * data)
{
	return SizeOfImage(data->width, data->height, data->encoding);
}

uint64_t LImageOperations::SizeOfImage(const TextureRef & ref)
{
	return SizeOfImage(ref->GetWidth(), ref->GetHeight(), ref->GetImageEncoding());
}
