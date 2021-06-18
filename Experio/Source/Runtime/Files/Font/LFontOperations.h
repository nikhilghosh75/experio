#pragma once
#include "FontReader.h"
#include "../../Math/FVector2.h"

#define PB_VARIANT_NOT_FOUND 15928

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

	static uint32_t GetCharCodeOfUV(const FontData& data, const FVector2& uv);

	static uint32_t GetIndexOfUV(const FontData& data, const FVector2& uv);

	static size_t GetIndexOfVariant(const FontData& data, EFontType variantType);

	static uint32_t GetMaxCharacterCode(const FontData& data);

	static bool HasAllCharsInRange(const FontData& data, uint32_t rangeStart, uint32_t rangeEnd);

	static bool HasVariantOfType(const FontData& data, EFontType variantType);

	static bool IsAlphabetSupported(const FontData& data, EAlphabet alphabet);

	static uint32_t SerializedSizeOf(const FontData& data);
	static uint32_t SerializedSizeOf(const uint32_t numCharacters);

	static uint32_t SizeOf(const FontData& data);

	static void SortCharacters(FontData& data);

	static EFontType StringToFontType(const std::string& str);
};