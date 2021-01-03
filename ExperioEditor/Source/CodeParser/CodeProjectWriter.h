#pragma once

#include "CodeProject.h"
#include <fstream>

class CodeProjectWriter
{
public:
	static void WriteToFile(const CodeProject& project, const std::string& filepath);

private:
	static void WriteClass(const CodeClass& codeClass, std::ofstream& outFile);

	static void WriteEnum(const CodeEnum& codeEnum, std::ofstream& outFile, ECodingLanguage language);
};