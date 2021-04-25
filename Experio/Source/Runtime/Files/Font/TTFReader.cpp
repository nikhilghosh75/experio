#include "TTFReader.h"
#include "LFontOperations.h"
#include "../../Debug/Debug.h"
#include "../../../ThirdParty/STB/stb_truetype.h"
#include "../../Debug/Profiler.h"
#include "../../Math/LMath.h"
#include <filesystem>
#include <stdlib.h>

#define PB_TTF_CHAR_RESOLUTION 32

TTFReader::TTFReader()
{

}

FontData* TTFReader::ReadFile(const char* filename)
{
	PROFILE_SCOPE_CATEGORY("TTF Reader", EProfilerCategory::Files);

	unsigned char* buffer = GetFileBuffer(filename);

	stbtt_fontinfo fontInfo;
	if (!stbtt_InitFont(&fontInfo, buffer, 0))
	{
		free(buffer);
		return nullptr;
	}

	FontData* fontData = new FontData();
	
	float defaultFontSize = GetDefaultFontSize(filename);
	fontData->defaultFontSize = (int)defaultFontSize;

	fontData->characters.reserve(fontInfo.numGlyphs);

	int bitmapResolution = GetBitmapResoluton(filename, fontInfo.numGlyphs);
	float scale = stbtt_ScaleForPixelHeight(&fontInfo, defaultFontSize);
	unsigned char* bitmap = (unsigned char*)malloc(bitmapResolution * bitmapResolution * sizeof(unsigned char));
	stbtt_bakedchar* bakedChars = new stbtt_bakedchar[fontInfo.numGlyphs];
	stbtt_BakeFontBitmap(buffer, 0,30, bitmap, bitmapResolution, bitmapResolution, 32, fontInfo.numGlyphs, bakedChars);

	for (int i = 0; i < fontInfo.numGlyphs; i++)
	{
		stbtt_bakedchar& bakedChar = bakedChars[i];
		std::cout << bakedChar.xoff << std::endl;
	}

	ImageData* imageData = new ImageData();
	imageData->data = bitmap;
	imageData->width = bitmapResolution;
	imageData->height = bitmapResolution;
	imageData->internalFormat = EImageInternalFormat::A;
	imageData->encoding = EImageEncoding::Alpha;

	TextureSlot& textureSlot = TextureManager::GetNextAvailibleSlot();
	TextureManager::ReserveSlot(textureSlot.slotID, "TTF Font Texture");
	textureSlot.texture = new Texture(imageData);

	fontData->fontTexture = TextureRef(textureSlot.slotID);

	int currentChar = 1;

	for (int i = 0; i < 65536; i++)
	{
		int glyphIndex = stbtt_FindGlyphIndex(&fontInfo, i);
		if (glyphIndex == 0)
			continue;

		stbtt_bakedchar& bakedChar = bakedChars[currentChar];

		FCharacterInfo charInfo;
		charInfo.charCode = i;

		int leftSideBearing;
		stbtt_GetCodepointHMetrics(&fontInfo, i, &charInfo.xAdvance, &leftSideBearing);
		charInfo.xAdvance *= scale;

		charInfo.uvCoordinates.min = FVector2((float)bakedChar.x0 / bitmapResolution, (float)bakedChar.y0 / bitmapResolution);
		charInfo.uvCoordinates.max = FVector2((float)bakedChar.x1 / bitmapResolution, (float)bakedChar.y1 / bitmapResolution);
		charInfo.offset = FVector2((float)bakedChar.xoff / bitmapResolution, (float)bakedChar.yoff / bitmapResolution);

		fontData->characters.push_back(charInfo);

		currentChar++;
	}

	/*
	std::vector<int> indexMap = GetIndexMap(&fontInfo);

	for (int i = 0; i < fontInfo.numGlyphs; i++)
	{
		if (indexMap[i] < 0)
		{
			continue;
		}

		stbtt_bakedchar& bakedChar = bakedChars[i];

		FCharacterInfo charInfo;
		
		int leftSideBearing;
		stbtt_GetGlyphHMetrics(&fontInfo, i, &charInfo.xAdvance, &leftSideBearing);

		charInfo.charCode = indexMap[i];

		// int x0, x1, y0, y1;
		// stbtt_GetGlyphBitmapBox(&fontInfo, i, scale, scale, &x0, &y0, &x1, &y1);
		
		charInfo.uvCoordinates.min = FVector2((float)bakedChar.x0 / bitmapResolution, (float)bakedChar.y0 / bitmapResolution);
		charInfo.uvCoordinates.max = FVector2((float)bakedChar.x1 / bitmapResolution, (float)bakedChar.y1 / bitmapResolution);
		charInfo.offset = FVector2((float)bakedChar.xoff / bitmapResolution, (float)bakedChar.yoff / bitmapResolution);

		// charInfo.uvCoordinates.min = FVector2((float)x0 / bitmapResolution, (float)y0 / bitmapResolution);
		// charInfo.uvCoordinates.max = FVector2((float)x1 / bitmapResolution, (float)y1 / bitmapResolution);

		fontData->characters.push_back(charInfo);
	}
	*/

	// LFontOperations::SortCharacters(*fontData);

	delete[] bakedChars;
	free(buffer);


	return fontData;
}

size_t TTFReader::SerializedSizeOf(const char* filename)
{
	unsigned char* buffer = GetFileBuffer(filename);

	stbtt_fontinfo fontInfo;
	if (!stbtt_InitFont(&fontInfo, buffer, 0))
	{
		return 0;
	}

	return LFontOperations::SerializedSizeOf(fontInfo.numGlyphs);
}

unsigned char* TTFReader::GetFileBuffer(const char* filename)
{
	size_t size = std::filesystem::file_size(filename);
	unsigned char* buffer;

	FILE* fontFile = fopen(filename, "rb");

	buffer = (unsigned char*)malloc(size);

	if (buffer == nullptr)
	{
		fclose(fontFile);
		return nullptr;
	}

	fread(buffer, size, 1, fontFile);
	fclose(fontFile);

	return buffer;
}

int TTFReader::GetBitmapResoluton(const char* filename, int numCharacters)
{
	std::string metaFilename = (std::string)filename + ".meta";
	std::ifstream inFile(metaFilename);
	if (!inFile.fail())
	{
		// If the meta file exists, then parse it and get the resolution
		std::string str;
		int resolution;

		for (int i = 0; i < 5; i++)
		{
			std::getline(inFile, str);
		}
		inFile >> str >> resolution;
		return resolution;
	}
	
	int resolutionToCheck = 32;
	while (resolutionToCheck < 65536)
	{
		int charResolution = LMath::Sqrt(resolutionToCheck * resolutionToCheck / numCharacters);
		if (charResolution > PB_TTF_CHAR_RESOLUTION)
		{
			return resolutionToCheck;
		}
		resolutionToCheck *= 2;
	}

	return resolutionToCheck;
}

std::vector<int> TTFReader::GetIndexMap(stbtt_fontinfo* info)
{
	std::vector<int> map;
	map.resize(info->numGlyphs + 3);

	for (size_t i = 0; i < map.size(); i++)
	{
		map[i] = -1;
	}

	for (int i = 0; i < 65535; i++)
	{
		int glyphIndex = stbtt_FindGlyphIndex(info, i);
		if (glyphIndex != 0)
		{
			map[glyphIndex] = i;
		}
	}

	return map;
}

float TTFReader::GetDefaultFontSize(const char* filename)
{
	// TO-DO: Add parsing of metadata
	return 36.f;
}
