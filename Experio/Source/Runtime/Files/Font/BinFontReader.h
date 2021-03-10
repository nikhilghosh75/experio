#pragma once

#include "FontReader.h"

class BinFontReader : public FontReader
{
public:
	FontData* ReadFile(const char* fileName);

	size_t SerializedSizeOf(const char* fileName);
};