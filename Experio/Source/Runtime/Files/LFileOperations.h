#pragma once
#include <string>

class LFileOperations
{
public:
	static bool DoesFileHaveExtension(std::string filePath, const char* extension);

	static std::string GetExtension(std::string filePath);

	static std::string GetFullFilePath(std::string filePath);
};