#pragma once
#include "Soundbank.h"

class SoundbankReader
{
public:
	static Soundbank ReadFromFile(const std::string& filepath);

private:
	static Soundbank ReadFromTextFile(const std::string& filepath);

	static Soundbank ReadFromBinaryFile(const std::string& filepath);
};