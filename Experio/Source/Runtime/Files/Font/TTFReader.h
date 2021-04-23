#pragma once

#include "FontReader.h"
#include <fstream>
#include <iostream>

struct stbtt_fontinfo;

class TTFReader : FontReader
{
public:
	TTFReader();

	FontData* ReadFile(const char* fileName);

	size_t SerializedSizeOf(const char* fileName);

private:
	unsigned char* GetFileBuffer(const char* filename);

	int GetBitmapResoluton(const char* filename, int numCharacters);

	std::vector<int> GetIndexMap(stbtt_fontinfo* info);

	float GetFontScale(const char* filename);
};