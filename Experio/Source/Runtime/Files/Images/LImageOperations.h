#pragma once
#include "ImageReader.h"
#include "../../Rendering/Managers/TextureManager.h"

class LImageOperations
{
public:
	static EImageEncoding EncodeBitsPerPixel(int bitsPerPixel);
	static EImageEncoding EncodeBytesPerPixel(int bytesPerPixel);

	static int BitsPerPixel(EImageEncoding encoding);
	static int BytesPerPixel(EImageEncoding encoding);

	static uint64_t SizeOfImage(int width, int height, EImageEncoding encoding);
	static uint64_t SizeOfImage(const ImageData* data);
	static uint64_t SizeOfImage(const Texture* texture);
	static uint64_t SizeOfImage(const TextureRef& ref);

	static std::string CompressionTypeToString(EImageCompressionType compressionType);
};