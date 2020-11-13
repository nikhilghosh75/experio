#pragma once
#include <string>
#include "Runtime/Containers/THashtable.h"
#include "Version.h"

struct FEditorProjectLanguages
{
	uint8_t cppVersion;
	uint16_t glslVersion; // Stored as preprocessor
};

class EditorProject
{
public:
	static THashtable<unsigned int, std::string> classes;

	static std::string projectName;
	static FVersion experioVersion;

	static FEditorProjectLanguages languages;

	static void ReadProjectFile(std::string filepath);

	static void ReadValueFiles();

	static void TempSetup();
};

unsigned int DefaultClassStringToInt(std::string name);