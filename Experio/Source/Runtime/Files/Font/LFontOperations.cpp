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
	case ECharacterSet::SYMBOL: return "SYMBOL";
	case ECharacterSet::THAI: return "THAI";
	case ECharacterSet::TURKISH: return "TURKISH";
	case ECharacterSet::UNICODE: return "UNICODE";
	case ECharacterSet::VIETNAMESE: return "VIETNAMESE";
	}
	return "";
}

ETextEncoding LFontOperations::GetEncoding(const FontData & data)
{
	uint32_t maxCharacterCode = GetMaxCharacterCode(data);
	if (maxCharacterCode < 128) return ETextEncoding::ASCII;
	if (maxCharacterCode < 256) return ETextEncoding::UTF8;
	if (maxCharacterCode < 16536) return ETextEncoding::UTF16;
	return ETextEncoding::UTF32;
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

uint32_t LFontOperations::SerializedSizeOf(const FontData & data)
{
	return 60 + data.characters.size() * 32;
}

uint32_t LFontOperations::SizeOf(const FontData & data)
{
	return 36 + data.characters.size() * 32;
}

void LFontOperations::SortCharacters(FontData& data)
{
	std::sort(data.characters.begin(), data.characters.end());
}
