#pragma once
#include "CodeProject.h"
#include <string>
#include <fstream>
#include "Runtime/Containers/TPair.h"

class CodeProjectReader
{
public:
	static CodeProject ReadFromFile(const std::string& filepath);

private:
	static void ParseGlobalAttribute(CodeProject& project, std::ifstream& inFile);

	static void ParseClasses(CodeProject& project, std::ifstream& inFile);

	static void ParseParams(CodeClass& codeClass, const std::string& str, ECodingLanguage language);

	static void ParseFunctions(CodeClass& codeClass, const std::string& str, ECodingLanguage language);

	static void ParseEnums(CodeProject& project, std::ifstream& inFile);

	static void ParseValues(CodeEnum& codeEnum, const std::string& str);

	static TPair<int, std::string> ParseValue(const std::string& str);

	static void ParseFunctions(CodeProject& project, std::ifstream& inFile);
};