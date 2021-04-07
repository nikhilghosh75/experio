#pragma once

#include <string>
#include <vector>
#include <fstream>

class ShaderMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);
};