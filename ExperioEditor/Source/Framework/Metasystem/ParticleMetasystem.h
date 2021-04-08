#pragma once

#include <string>
#include <vector>
#include <fstream>

class ParticleMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);
};