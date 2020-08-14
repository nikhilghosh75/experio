#pragma once
#include <string>

class LFileOperations
{
public:
	static bool DoesFileHaveExtension(std::string filePath, const char* extension);
};