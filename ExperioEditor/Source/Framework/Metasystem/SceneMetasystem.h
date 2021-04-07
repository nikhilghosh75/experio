#pragma once

#include <string>
#include <vector>
#include <fstream>

class SceneMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);
};