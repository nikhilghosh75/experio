#pragma once
#include <string>
#include <vector>
#include <iostream>

class FontMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);
};