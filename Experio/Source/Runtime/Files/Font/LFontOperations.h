#pragma once
#include "FontReader.h"

enum class EAlphabet
{
	Arabic,
	Armenian,
	Basic,
	Bengali,
	Cyrillic,
	Devanagari,
	Greek,
	Gujarati,
	Gurmukhi,
	Hebrew,
	Kannada, // Last Alphabet
	Latin,
	Mandaic,
	NKo,
	Oriya,
	Samaritan,
	Syriac,
	Tamil,
	Telugu,
	Thaana
};

class LFontOperations
{
public:
	static std::string CharsetToString(ECharacterSet charSet);

	static ETextEncoding GetEncoding(const FontData& data);

	static uint32_t GetMaxCharacterCode(const FontData& data);

	static bool HasAllCharsInRange(const FontData& data, uint32_t rangeStart, uint32_t rangeEnd);

	static bool IsAlphabetSupported(const FontData& data, EAlphabet alphabet);

	static uint32_t SerializedSizeOf(const FontData& data);

	static uint32_t SizeOf(const FontData& data);

	static void SortCharacters(FontData& data);
};