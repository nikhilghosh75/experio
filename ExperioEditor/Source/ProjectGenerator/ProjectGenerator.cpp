#include "ProjectGenerator.h"
#include "VisualStudioProject.h"

namespace ExperioEditor::ProjectGenerator
{

void GenerateWindowsProject(const std::string & projectPath, const FNewProjectSettings & settings)
{
	VisualStudio::VSSolution solution;
	GenerateGameProject(projectPath, settings.projectName, solution);
	GenerateEditorProject(projectPath + "/Editor", solution);
	GenerateExecutableProject(projectPath + "/Generated", solution);
	solution.GenerateSolutionFile(projectPath);
}

void GenerateGameProject(const std::string & gamePath, const std::string& projectName)
{
	VisualStudio::VSProject project(projectName);

}

void GenerateEditorProject(const std::string & editorPath, VisualStudio::VSSolution& solution)
{
}

void GenerateExecutableProject(const std::string & executablePath, VisualStudio::VSSolution& solution)
{
}

}
