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

	void Setup();

	void Run();

	void Shutdown();

private:
	void ExecuteCommand(char* command);
};