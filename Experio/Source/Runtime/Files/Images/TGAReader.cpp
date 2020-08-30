#include "TGAReader.h"
#include "../../Debug/Debug.h"
#include "../../Debug/TempProfiler.h"
#include <fstream>

TGAReader::TGAReader()
{
}

ImageData* TGAReader::ReadFile(const char * fileName)
{
	TempProfiler("Reading TGA");

	std::fstream tgaFile(fileName);

	std::uint8_t header[18];
	std::uint8_t decompressed[12] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::uint8_t iscompressed[12] = { 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	tgaFile.read((char*)header, 18);

	std::uint8_t bitsPerPixel;
	unsigned int width, height;
	EImageEncoding encoding;
	char* pixelData;

	if (!std::memcmp(decompressed, &header, 12))
	{
		bitsPerPixel = header[16];
		width = header[13] * 256 + header[12];
		height = header[15] * 256 + header[14];

		switch (bitsPerPixel)
		{
		case 24:
			encoding = EImageEncoding::Truecolor;
			break;
		case 32:
			encoding = EImageEncoding::TruecolorAlpha;
			break;
		default:
			Debug::LogError("Invalid File Format. Required: 24 or 32 Bit Image.");
			return nullptr;
		}

		unsigned int size = ((width * bitsPerPixel + 31) / 32) * 4 * height;
		pixelData = new char[size];
		tgaFile.read(pixelData, size);
	}
	else if (!std::memcmp(iscompressed, &header, sizeof(12)))
	{
		bitsPerPixel = header[16];
		width = header[13] * 256 + header[12];
		height = header[15] * 256 + header[14];

		switch (bitsPerPixel)
		{
		case 24:
			encoding = EImageEncoding::Truecolor;
			break;
		case 32:
			encoding = EImageEncoding::TruecolorAlpha;
			break;
		default:
			Debug::LogError("Invalid File Format. Required: 24 or 32 Bit Image.");
			return nullptr;
		}

		unsigned int size = ((width * bitsPerPixel + 31) / 32) * 4 * height;
		unsigned int numPixels = width * height;

		char pixel[4] = { 0, 0, 0, 0 };
		int currentByte = 0;
		std::size_t currentPixel = 0;
		std::uint8_t chunckHeader = 0;
		int bytesPerPixel = (bitsPerPixel / 8);
		pixelData = new char[width * height * 4];

		do
		{
			tgaFile.read((char*)chunckHeader, 1);
			if (chunckHeader < 128)
			{
				chunckHeader++;
				for (int i = 0; i < chunckHeader; i++, currentPixel)
				{
					tgaFile.read((char*)pixel, bytesPerPixel);

					pixelData[currentByte++] = pixel[2];
					pixelData[currentByte++] = pixel[1];
					pixelData[currentByte++] = pixel[0];
					if (bitsPerPixel == 32)
					{
						pixelData[currentByte++] = pixel[3];
					}
					else
					{
						pixelData[currentByte++] = 0;
					}
				}
			}
			else
			{
				chunckHeader -= 127;
				tgaFile.read((char*)pixel, bytesPerPixel);
				for (int i = 0; i < chunckHeader; i++, currentPixel++)
				{
					pixelData[currentByte++] = pixel[2];
					pixelData[currentByte++] = pixel[1];
					pixelData[currentByte++] = pixel[0];
					if (bitsPerPixel == 32)
					{
						pixelData[currentByte++] = pixel[3];
					}
					else
					{
						pixelData[currentByte++] = 0;
					}
				}
			}
		} 
		while (currentPixel < numPixels);
	}
	else
	{
		Debug::LogError("Invalid File Format. Required: 24 or 32 Bit Image.");
		return nullptr;
	}
	ImageData* returnData = new ImageData();
	returnData->encoding = encoding;
	returnData->fileType = EImageFileType::TGA;
	returnData->height = height;
	returnData->width = width;
	returnData->data = pixelData;

	return returnData;
}