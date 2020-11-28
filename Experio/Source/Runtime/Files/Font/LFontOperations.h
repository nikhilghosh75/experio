#pragma once
#include "FontReader.h"

class LFontOperations
{
public:
	static ETextEncoding GetEncoding(const FontData& data);

	static uint32_t GetMaxCharacterCode(const FontData& data);
};