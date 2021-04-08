#pragma once
#include <string>
#include <vector>
#include <iostream>

class MeshMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);
};