#pragma once
#include "../FileReader.h"
#include <string>
#include <vector>
#include "../../Math/FRect.h"
#include "../../Rendering/Texture.h"

enum class ECharacterSet : uint8_t
{
	ANSI = 0x00,
	DEFAULT = 0x01,
	SYMBOL = 0x02,
	UNICODE = 0x03,
	MAC = 0x4D,
	SHIFTJIS = 0x80,
	HANGUL = 0x81,
	JOHAB = 0x82,
	GB2312 = 0x86,
	CHINESEBIGS = 0x88,
	GREEK = 0xA1,
	TURKISH = 0xA2,
	VIETNAMESE = 0xA3,
	HEBREW = 0xB1,
	ARABIC = 0xB2,
	BALTIC = 0xBA,
	RUSSIAN = 0xCC,
	THAI = 0xDE,
	EASTEUROPE = 0xEE,
	OEMCHARSET = 0xFF
};

enum class ETextEncoding : uint8_t
{
	ASCII = 7,
	UTF8 = 8,
	UTF16 = 16,
	UTF32 = 32
};

enum class EFontFileType : uint8_t
{
	FNT,
	TTF,
	OTF
};

struct FCharacterInfo
{
	unsigned int charCode;
	int xAdvance;
	FRect uvCoordinates;
	FVector2 offset;
};

class FontData : TFileData
{
public:
	int defaultFontSize;

	std::string name;

	Texture* fontTexture;

	ECharacterSet charset;

	std::vector<FCharacterInfo> characters;

	EFontFileType fileType;
};

class FontReader : FileReader<FontData>
{
public:
	FontReader() { };
};