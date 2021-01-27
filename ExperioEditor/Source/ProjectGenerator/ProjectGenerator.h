#pragma once
#include <string>
#include "../Framework/Version.h"
#include "VisualStudioSolution.h"

namespace ExperioEditor::ProjectGenerator
{
	struct FNewProjectSettings
	{
		std::string projectName;
		FVersion version;
		std::string username;
		std::string experioPath;
		std::string experioEditorPath;
		std::string experioBinariesPath;
		std::string experioDependenciesPath;
	};

	void GenerateWindowsProject(const std::string& projectPath, const FNewProjectSettings& settings);

	void GenerateGameProject(const std::string& gamePath, const std::string& projectName, VisualStudio::VSSolution& solution);

	void GenerateEditorProject(const std::string & projectPath, const std::string& projectName, VisualStudio::VSSolution& solution);

	void GenerateExeProject(const std::string& projectPath, const std::string& projectName, VisualStudio::VSSolution& solution);

	void GenerateUserFile(const std::string& projectPath, const FNewProjectSettings& settings);

	void GenerateProjectFile(const std::string& projectPath, const FNewProjectSettings& settings);

	void GenerateFolders(const std::string& projectPath);

	void GenerateConfig(const std::string& projectPath, const std::string& projectName, FVersion version);

	void GenerateTagFile(const std::string& filepath, const std::string& projectName, FVersion version);
	void GenerateLayerFile(const std::string& filepath, const std::string& projectName, FVersion version);

	void GenerateCode(const std::string& projectPath);
}