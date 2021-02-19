#include "HubApplication.h"
#include "HubCommands.h"
#include "Runtime/Containers/LString.h"
#include "ThirdParty/toml++/toml.h"
#include <filesystem>
#include <fstream>
#include <iostream>

std::string HubApplication::experioFilepath;
std::string HubApplication::experioEditorFilepath;
std::string HubApplication::experioDependenciesFilepath;
std::string HubApplication::experioBinariesFilepath;
std::string HubApplication::standardAssetsFilepath;

bool HubApplication::foundFilepaths = false;

HubApplication* HubApplication::hubApplication;

HubApplication::HubApplication()
{
	hubApplication = this;
}

void HubApplication::Setup()
{
	functions.Insert("help", Help);
	functions.Insert("version", Version);
	functions.Insert("create-project", CreateProject);

	ReadUserFile();
	if (!foundFilepaths)
	{
		FindInternalPaths();
	}
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
	if (commandStr == "quit")
	{
		isRunning = false;
		return;
	}

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

void HubApplication::ReadUserFile()
{
	std::ifstream inFile("user.pbuser");
	
	// This file may not exist
	if (inFile.bad())
	{
		return;
	}

	toml::table table = toml::parse_file("user.pbuser");

	HubApplication::experioFilepath = table["Filepaths"]["Experio"].value_or("");
	HubApplication::experioEditorFilepath = table["Filepaths"]["ExperioEditor"].value_or("");
	HubApplication::experioBinariesFilepath = table["Filepaths"]["Binaries"].value_or("");
	HubApplication::experioDependenciesFilepath = table["Filepaths"]["Dependencies"].value_or("");

	foundFilepaths = true;
}

void HubApplication::FindInternalPaths()
{
	for (auto& p : std::filesystem::recursive_directory_iterator("C:/"))
	{
		// Currently set for only one engine version
		if (p.path().filename().string() == "installation.pbuser")
		{
			std::filesystem::copy_file(p.path(), "user.pbuser");
		}
	}
}

