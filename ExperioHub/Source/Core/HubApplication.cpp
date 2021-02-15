#include "HubApplication.h"
#include "HubCommands.h"
#include "Runtime/Containers/LString.h"
#include <iostream>

HubApplication* HubApplication::hubApplication;

HubApplication::HubApplication()
{
	hubApplication = this;
}

void HubApplication::Setup()
{
	functions.Insert("help", Help);
	functions.Insert("version", Version);
}

void HubApplication::Run()
{
	isRunning = true;
	char command[512];
	memset(command, 0, 512);

	while (isRunning)
	{
		std::cin.getline(command, 512);
		ExecuteCommand(command);
	}
}

void HubApplication::Shutdown()
{

}

void HubApplication::ExecuteCommand(char * command)
{
	std::string commandStr(command);
	std::vector<std::string> args = LString::SeperateStringByChar(commandStr, ' ');

	CommandFunction function;
	bool found = functions.SafeGet(args[0], function);
	if (found)
	{
		function(args);
	}
	else
	{
		std::cout << "This was not a recognized command. Please choose a new command or type help for more info" << std::endl;
	}
}

