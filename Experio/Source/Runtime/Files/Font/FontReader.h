#pragma once
#include <string>
#include <vector>
#include "../../Math/FRect.h"
#include "../../Rendering/Texture.h"
#include "../../Rendering/Managers/TextureManager.h"

class FontData;
class FontRef;

enum class ECharacterSet : uint8_t
{
	ANSI = 0x00,
	DEFAULT = 0x01,
	SYMBOLSET = 0x02,
	// UNICODE = 0x03,
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
	OTF,
	Binary
};

enum class EFontType : uint8_t
{
	Normal = 0,
	Bold = 1,
	Italics = 2,
	BoldItalics = 3
};

struct FFontVariant
{
	uint16_t dataIndex;
	EFontType type;
	bool loaded = true;

	FFontVariant() = default;
	FFontVariant(EFontType fontType)
	{
		type = fontType;
	}
};

struct FCharacterInfo
{
	unsigned int charCode;
	int xAdvance;
	FRect uvCoordinates;
	FVector2 offset;

	bool operator<(const FCharacterInfo& other) const
	{
		return this->charCode < other.charCode;
	}

	bool operator>(const FCharacterInfo& other) const
	{
		return this->charCode > other.charCode;
	}
};

class FontData
{
public:
	int defaultFontSize;

	std::string name;

	TextureRef fontTexture;

	ECharacterSet charset;

	ETextEncoding encoding;

	std::vector<FCharacterInfo> characters;

	std::vector<FFontVariant> variants;

	FCharacterInfo& GetCharacterFromCode(unsigned int code)
	{
		return characters[BinarySearchForChar(code, 0, characters.size())];
		/*
		for (int i = 0; i < characters.size(); i++)
		{
			if (characters[i].charCode == code)
			{
				return characters[i];
			}
		}
		return characters[0];
		*/
	}

	uint32_t IndexOfCharacterCode(unsigned int code) const
	{
		return BinarySearchForChar(code, 0, characters.size());
	}

	bool HasCharacter(unsigned int code) const
	{
		return characters[BinarySearchForChar(code, 0, characters.size())].charCode == code;
	}

	unsigned int GetBitmapWidth() const
	{
		return fontTexture->GetWidth();
	}

	unsigned int GetBitmapHeight() const
	{
		return fontTexture->GetHeight();
	}

private:
	uint32_t BinarySearchForChar(unsigned int charCode, uint32_t lower, uint32_t range) const
	{
		if (range == 0)
		{
			return lower;
		}

		uint32_t mid = lower + (range / 2);
		if (characters[mid].charCode == charCode) return mid;
		
		if (characters[mid].charCode > charCode) return BinarySearchForChar(charCode, lower, (range / 2));
		return BinarySearchForChar(charCode, mid + 1, (range / 2));
	}
};

class FontReader
{
public:
	FontReader() { };

	static FontData* ReadFile(const char* fileName);

	static FontData* ReadFile(unsigned int assetIndex);

	static size_t SerializedSizeOf(const char* filename);

	static size_t SerializedSizeOf(unsigned int assetIndex);

	static std::vector<FFontVariant> ReadVariantsFromMeta(const char* filename);
};