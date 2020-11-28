#include "LFontOperations.h"

ETextEncoding LFontOperations::GetEncoding(const FontData & data)
{
	uint32_t maxCharacterCode = GetMaxCharacterCode(data);
	if (maxCharacterCode < 128) return ETextEncoding::ASCII;
	if (maxCharacterCode < 256) return ETextEncoding::UTF8;
	if (maxCharacterCode < 16536) return ETextEncoding::UTF16;
	return ETextEncoding::UTF32;
}

uint32_t LFontOperations::GetMaxCharacterCode(const FontData & data)
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
