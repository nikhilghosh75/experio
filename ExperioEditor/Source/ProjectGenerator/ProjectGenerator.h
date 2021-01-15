#pragma once
#include <string>
#include "VisualStudioSolution.h"

namespace ExperioEditor::ProjectGenerator
{
	struct FNewProjectSettings
	{
		std::string projectName;
	};

	void GenerateWindowsProject(const std::string& projectPath, const FNewProjectSettings& settings);

	void GenerateGameProject(const std::string& gamePath, const std::string& projectName, VisualStudio::VSSolution& solution);

	void GenerateEditorProject(const std::string& editorPath, VisualStudio::VSSolution& solution);

	void GenerateExecutableProject(const std::string& executablePath, VisualStudio::VSSolution& solution);
}