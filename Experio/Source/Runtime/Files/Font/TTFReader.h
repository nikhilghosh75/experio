#pragma once

#include "FontReader.h"
#include <fstream>
#include <iostream>

class TTFReader : FontReader
{
public:
	TTFReader();

	FontData* ReadFile(const char* fileName);

	size_t SerializedSizeOf(const char* fileName);

private:
	unsigned char* GetFileBuffer(const char* filename);

	int GetBitmapResoluton(const char* filename, int numCharacters);
};