#include "../Core/HubApplication.h"
#include "../Core/HubCommands.h"
#include "../ProjectGenerator/ProjectGenerator.h"
#include "Framework/Version.h"
#include "Runtime/Core/Core.h"

int CreateProject(const std::vector<std::string>& args)
{
	if (args.size() < 2)
	{
		return 1;
	}

	FVersion version;

	// Extend this later
	if (args.size() > 3)
	{
		if (args[3] == "-v" || args[3] == "--version")
		{
			version = FVersion(args[4]);
		}
	}
	else
	{
		version = FVersion(EXPERIO_BUILD_MAJOR, EXPERIO_BUILD_MINOR, EXPERIO_BUILD_PATCH);
	}

	ExperioEditor::ProjectGenerator::FNewProjectSettings settings;
	settings.version = version;
	settings.experioBinariesPath = HubApplication::experioBinariesFilepath;
	settings.experioDependenciesPath = HubApplication::experioDependenciesFilepath;
	settings.experioEditorPath = HubApplication::experioEditorFilepath;
	settings.experioPath = HubApplication::experioFilepath;
	settings.projectName = args[2];

	ExperioEditor::ProjectGenerator::GenerateWindowsProject(args[1], settings);

	return 0;
}