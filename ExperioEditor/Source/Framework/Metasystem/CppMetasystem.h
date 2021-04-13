#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../CreateMenu.h"

class CppMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);

private:
	static ECodeClassBase GetCodeClassBase(const std::string& filepath);

	static void GenerateComponentMetadata(const std::string& filepath, std::ofstream& outFile);

	static std::string GetComponentCategory(const std::string& filepath);

	static void GenerateLibraryMetadata(const std::string& filepath, std::ofstream& outFile);
};