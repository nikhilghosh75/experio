#pragma once

#include "Runtime/Core/Platform.h"
#include "Runtime/Framework/GUID128.h"
#include "CodeParser/CodeParser.h"

namespace ExperioEditor::VisualStudio
{
enum class EVSProjectType
{
	CSharp,
	Cpp,
	Database,
	MicroFramework,
	ProjectFolder
};

enum class EVSConfiguration
{
	StaticLibrary,
	DynamicLibrary,
	Executable
};

class VSProject
{
public:
	VSProject(const std::string& name);

	std::string name;
	GUID128 id;

	std::string filepath;

	EVSProjectType projectType = EVSProjectType::Cpp;
	EArchitecture architecture = EArchitecture::x64;

	std::string outputDirectory;
	
	std::string intermediateDirectory;

	std::vector<std::string> includePaths;
	std::vector<std::string> compilePaths;

	std::vector<std::string> preprocessorDefines;

	std::vector<std::string> additionalIncludeDirectories;

	EVSConfiguration debugConfiguration;
	EVSConfiguration releaseConfiguration;

	ECodingLanguage language;
	uint8_t version;

	void SetConfiguration(EVSConfiguration configuration);

	void GenerateProjectFile(const std::string& filepath);

private:
	// Move Later
	static std::string ArchitectureToString(EArchitecture architecture);

	static std::string ConfigurationToString(EVSConfiguration configuration);
};
}