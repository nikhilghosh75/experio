#pragma once
#include "Runtime/Containers/THashtable.h"
#include "Framework/Version.h"
#include <vector>
#include <string>
#include <functional>

// Help
// Version
// Create
// Quit

typedef std::function<int(const std::vector<std::string>&)> CommandFunction;

class HubApplication
{
	bool isRunning = false;

	static HubApplication* hubApplication;
public:
	THashtable<std::string, CommandFunction, StringHashFunction> functions;

	HubApplication();

	static const HubApplication* Get() { return hubApplication; };

	static std::string experioFilepath;
	static std::string experioEditorFilepath;
	static std::string experioDependenciesFilepath;
	static std::string experioBinariesFilepath;
	static std::string standardAssetsFilepath;

	static bool foundFilepaths;

	void Setup();

	void Run();

	void Shutdown();

private:
	void ExecuteCommand(char* command);

	void ReadUserFile();

	void FindInternalPaths();
};