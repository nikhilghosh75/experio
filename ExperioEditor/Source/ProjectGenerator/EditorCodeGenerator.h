#pragma once
#include <string>

class EditorCodeGenerator
{
public:
	static void GenerateBuild(const std::string& editorPath);

	static void GenerateRCCPP(const std::string& editorPath);

	static void GenerateMain(const std::string& editorPath);

	static void GenerateExecutable(const std::string& generatedPath);
};