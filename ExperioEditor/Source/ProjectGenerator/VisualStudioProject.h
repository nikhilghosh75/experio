#pragma once

#include "Runtime/Core/Platform.h"
#include "Runtime/Framework/GUID128.h"
#include "../CodeParser/CodeParser.h"

namespace ExperioEditor::VisualStudio
{
class VSProject
{
public:
	std::string name;
	GUID128 id;

	EArchitecture architecture;

	std::string outputDirectory;
	
	std::string intermediateDirectory;

	std::vector<std::string> includePaths;
	std::vector<std::string> compilePaths;

	std::vector<std::string> preprocessorDefines;

	std::vector<std::string> additionalIncludeDirectories;

	ECodingLanguage language;
	uint8_t version;

	void GenerateProjectFile(std::string& filepath);

private:
	// Move Later
	static std::string ArchitectureToString(EArchitecture architecture);
};
}