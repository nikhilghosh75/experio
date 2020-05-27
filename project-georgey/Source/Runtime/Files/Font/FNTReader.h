#pragma once

#include "FontReader.h"
#include <fstream>
#include <iostream>

class FNTReader : FontReader
{
public:
	FNTReader();

	FontData* ReadFile(const char* fileName) override;

	std::string StripAfterEqualSign(const std::string& s);

private:
	std::string StripQuotes(const std::string& s);

	ECharacterSet ParseCharacterSet(const std::string& s);

	FCharacterInfo ReadCharacterData(ifstream& fntStream);
};