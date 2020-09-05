#pragma once

#include "FontReader.h"
#include <fstream>
#include <iostream>

class FNTReader : FontReader
{
public:
	FNTReader();

	FontData* ReadFile(const char* fileName) override;

private:
	std::string StripAfterEqualSign(const std::string& s);

	std::string StripQuotes(const std::string& s);

	ECharacterSet ParseCharacterSet(const std::string& s);

	FCharacterInfo ReadCharacterData(std::ifstream& fntStream, float width, float height);
};