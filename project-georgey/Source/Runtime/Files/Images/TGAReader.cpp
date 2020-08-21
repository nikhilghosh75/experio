#include "TGAReader.h"
#include "../../Debug/GDebug.h"
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
			GDebug::LogError("Invalid File Format. Required: 24 or 32 Bit Image.");
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
			GDebug::LogError("Invalid File Format. Required: 24 or 32 Bit Image.");
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
		GDebug::LogError("Invalid File Format. Required: 24 or 32 Bit Image.");
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

/*
Tga::Tga(const char* FilePath)
{
	std::fstream hFile(FilePath, std::ios::in | std::ios::binary);
	if (!hFile.is_open()){throw std::invalid_argument("File Not Found.");}

	std::uint8_t Header[18] = {0};
	std::vector<std::uint8_t> ImageData;
	static std::uint8_t DeCompressed[12] = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	static std::uint8_t IsCompressed[12] = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

	hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));

	if (!std::memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
	{
		BitsPerPixel = Header[16];
		width  = Header[13] * 256 + Header[12];
		height = Header[15] * 256 + Header[14];
		size  = ((width * BitsPerPixel + 31) / 32) * 4 * height;

		if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
		{
			hFile.close();
			throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
		}

		ImageData.resize(size);
		ImageCompressed = false;
		hFile.read(reinterpret_cast<char*>(ImageData.data()), size);
	}
	else if (!std::memcmp(IsCompressed, &Header, sizeof(IsCompressed)))
	{
		BitsPerPixel = Header[16];
		width  = Header[13] * 256 + Header[12];
		height = Header[15] * 256 + Header[14];
		size  = ((width * BitsPerPixel + 31) / 32) * 4 * height;

		if ((BitsPerPixel != 24) && (BitsPerPixel != 32))
		{
			hFile.close();
			throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
		}

		PixelInfo Pixel = {0};
		int CurrentByte = 0;
		std::size_t CurrentPixel = 0;
		ImageCompressed = true;
		std::uint8_t ChunkHeader = {0};
		int BytesPerPixel = (BitsPerPixel / 8);
		ImageData.resize(width * height * sizeof(PixelInfo));

		do
		{
			hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

			if(ChunkHeader < 128)
			{
				++ChunkHeader;
				for(int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
			else
			{
				ChunkHeader -= 127;
				hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

				for(int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
				{
					ImageData[CurrentByte++] = Pixel.B;
					ImageData[CurrentByte++] = Pixel.G;
					ImageData[CurrentByte++] = Pixel.R;
					if (BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
				}
			}
		} while(CurrentPixel < (width * height));
	}
	else
	{
		hFile.close();
		throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit TGA File.");
	}

	hFile.close();
	this->Pixels = ImageData;
}

*/