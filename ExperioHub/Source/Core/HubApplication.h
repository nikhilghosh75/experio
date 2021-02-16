#pragma once
#include "Runtime/Containers/THashtable.h"
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
	static std::string experioEditorFilePath;
	static std::string experioDependenciesFilePath;
	static std::string experioBinariesFilePath;
	static std::string standardAssetsFilePath;

	void Setup();

	void Run();

	void Shutdown();

private:
	void ExecuteCommand(char* command);
};