#pragma once
#include "FontReader.h"

class LFontOperations
{
public:
	static std::string CharsetToString(ECharacterSet charSet);

	static ETextEncoding GetEncoding(const FontData& data);

	static uint32_t GetMaxCharacterCode(const FontData& data);

	static void SortCharacters(FontData& data);
};