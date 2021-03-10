#include "TerminalCommands.h"
#include "../CodeParser/CodeAnalytics.h"
#include "../Framework/EditorProject.h"

/*
	code-stats
*/

int CodeStats(const std::vector<std::string>& args)
{
	if (args.size() != 1)
	{
		return INVALID_ARG_COUNT;
	}

	CodeAnalytics analytics;
	GenerateCodeAnalyticsFromProject(analytics, EditorProject::gameProject);

	Terminal::Print("Classes: " + std::to_string(analytics.numClasses));
	Terminal::Print("Enums: " + std::to_string(analytics.numEnums));
	Terminal::Print("Functions: " + std::to_string(analytics.numFunctions));
	Terminal::Print("# of Lines: " + std::to_string(analytics.numLines));
	Terminal::Print("# of Files: " + std::to_string(analytics.numFiles));
	Terminal::Print("");
	Terminal::Print("Components: " + std::to_string(analytics.numComponents));
	Terminal::Print("Libraries: " + std::to_string(analytics.numLibraries));

	return 0;
}