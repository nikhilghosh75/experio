#include "LFontOperations.h"
#include <algorithm>

std::string LFontOperations::CharsetToString(ECharacterSet charSet)
{
	switch (charSet)
	{
	case ECharacterSet::ANSI: return "ANSI";
	case ECharacterSet::ARABIC: return "ARABIC";
	case ECharacterSet::BALTIC: return "BALTIC";
	case ECharacterSet::CHINESEBIGS: return "CHINESE BIGS";
	case ECharacterSet::DEFAULT: return "DEFAULT";
	case ECharacterSet::EASTEUROPE: return "EASTERN EUROPE";
	case ECharacterSet::GB2312: return "SIMPLIFIED CHINESE";
	case ECharacterSet::GREEK: return "GREEK";
	case ECharacterSet::HANGUL: return "HANGUL";
	case ECharacterSet::HEBREW: return "HEBREW";
	case ECharacterSet::JOHAB: return "KOREAN";
	case ECharacterSet::MAC: return "MAC";
	case ECharacterSet::OEMCHARSET: return "WINDOWS";
	case ECharacterSet::RUSSIAN: return "RUSSIAN";
	case ECharacterSet::SHIFTJIS: return "JAPANESE";
	case ECharacterSet::SYMBOLSET: return "SYMBOL";
	case ECharacterSet::THAI: return "THAI";
	case ECharacterSet::TURKISH: return "TURKISH";
	// case ECharacterSet::UNICODE: return "UNICODE";
	case ECharacterSet::VIETNAMESE: return "VIETNAMESE";
	}
	return "";
}

std::string LFontOperations::FontTypeToString(EFontType fontType)
{
	switch (fontType)
	{
	case EFontType::Bold: return "Bold";
	case EFontType::BoldItalics: return "Bold Italic";
	case EFontType::Italics: return "Italic";
	case EFontType::Normal: return "Normal";
	}
	return std::string();
}

ETextEncoding LFontOperations::GetEncoding(const FontData & data)
{
	uint32_t maxCharacterCode = GetMaxCharacterCode(data);
	if (maxCharacterCode < 128) return ETextEncoding::ASCII;
	if (maxCharacterCode < 256) return ETextEncoding::UTF8;
	if (maxCharacterCode < 16536) return ETextEncoding::UTF16;
	return ETextEncoding::UTF32;
}

uint32_t LFontOperations::GetCharCodeOfUV(const FontData & data, const FVector2 & uv)
{
	for (uint32_t i = 0; i < data.characters.size(); i++)
	{
		if (data.characters[i].uvCoordinates.IsInside(uv))
		{
			return data.characters[i].charCode;
		}
	}
	return 0;
}

uint32_t LFontOperations::GetIndexOfUV(const FontData& data, const FVector2& uv)
{
	for (uint32_t i = 0; i < data.characters.size(); i++)
	{
		if (data.characters[i].uvCoordinates.IsInside(uv))
		{
			return i;
		}
	}
	return 0;
}

size_t LFontOperations::GetIndexOfVariant(const FontData& data, EFontType variantType)
{
	if (data.variants.empty())
		return PB_VARIANT_NOT_FOUND;

	for (size_t i = 0; i < data.variants.size(); i++)
	{
		if (data.variants[i].type == variantType)
			return i;
	}

	return PB_VARIANT_NOT_FOUND;
}

uint32_t LFontOperations::GetMaxCharacterCode(const FontData& data)
{
	uint32_t max = 0;
	for (uint32_t i = 0; i < data.characters.size(); i++)
	{
		if (data.characters[i].charCode > max)
		{
			max = data.characters[i].charCode;
		}
	}
	return max;
}

bool LFontOperations::HasAllCharsInRange(const FontData & data, uint32_t rangeStart, uint32_t rangeEnd)
{
	uint32_t startIndex = data.IndexOfCharacterCode(rangeStart);
	uint32_t endIndex = data.IndexOfCharacterCode(rangeEnd);

	if ((endIndex - startIndex) != (rangeEnd - rangeStart)) 
		return false;

	for (uint32_t i = 0; i < (endIndex - startIndex) + 1; i++)
	{
		if (data.characters[i + startIndex].charCode != rangeStart + i) 
			return false;
	}
	return true;
}

bool LFontOperations::HasVariantOfType(const FontData& data, EFontType variantType)
{
	if (data.variants.empty())
		return false;
	
	for (size_t i = 0; i < data.variants.size(); i++)
	{
		if (data.variants[i].type == variantType)
			return true;
	}

	return false;
}

bool LFontOperations::IsAlphabetSupported(const FontData & data, EAlphabet alphabet)
{
	switch (alphabet)
	{
	case EAlphabet::Basic:
		return HasAllCharsInRange(data, 33, 125);
	case EAlphabet::Latin:
		return HasAllCharsInRange(data, 161, 591);
	case EAlphabet::Greek:
		return HasAllCharsInRange(data, 880, 1022);
	case EAlphabet::Cyrillic:
		return HasAllCharsInRange(data, 1024, 1327);
	case EAlphabet::Armenian:
		return HasAllCharsInRange(data, 1328, 1423);
	case EAlphabet::Hebrew:
		return HasAllCharsInRange(data, 1424, 1524);
	case EAlphabet::Arabic:
		return HasAllCharsInRange(data, 1536, 1791);
	case EAlphabet::Syriac:
		return HasAllCharsInRange(data, 1824, 1871);
	case EAlphabet::Thaana:
		return HasAllCharsInRange(data, 1920, 1969);
	case EAlphabet::NKo:
		return HasAllCharsInRange(data, 1984, 2042);
	case EAlphabet::Samaritan:
		return HasAllCharsInRange(data, 2048, 2110);
	case EAlphabet::Mandaic:
		return HasAllCharsInRange(data, 2112, 2139);
	case EAlphabet::Devanagari:
		return HasAllCharsInRange(data, 2304, 2431);
	case EAlphabet::Bengali:
		return HasAllCharsInRange(data, 2432, 2557);
	}
	return false;
}

uint32_t LFontOperations::SerializedSizeOf(const FontData & data)
{
	return 60 + data.characters.size() * 32;
}

uint32_t LFontOperations::SerializedSizeOf(const uint32_t numCharacters)
{
	return 60 + numCharacters * 32;
}

uint32_t LFontOperations::SizeOf(const FontData & data)
{
	return 36 + data.characters.size() * 32;
}

void LFontOperations::SortCharacters(FontData& data)
{
	std::sort(data.characters.begin(), data.characters.end());
}

EFontType LFontOperations::StringToFontType(const std::string& str)
{
	if (str == "Bold")
		return EFontType::Bold;
	else if (str == "BoldItalic")
		return EFontType::BoldItalics;
	else if (str == "Italic")
		return EFontType::Italics;
	return EFontType::Normal;
}

std::string LFontOperations::UnicodeToString(unsigned int unicode)
{
	const std::string unicodeTable[] = {
		"Null", "Start of heading", "Start of text", "End of text", // 3
		"End of transmission", "Enquity", "Acknowledge", "Bell", // 7
		"Backspace", "Horizontal Tab", "New Line", "Vertical Tab", // 11
		"New Page", "Return", "Shift Out", "Shift In", // 15
		"Data Link", "Device Control 1", "Device Control 2", "Device Control 3" // 19
	};

	if (unicode >= 20)
		return std::to_string(unicode);

	return unicodeTable[unicode];
}
