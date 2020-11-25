#pragma once
#include <string>
#include "Runtime/Containers/TTypedTree.h"
#include "ThirdParty/toml++/toml.h"

class ProjectSettingModule
{
public:
	std::string settingsFile;

	virtual void ReadFromTable(toml::table table) = 0;

	virtual void GenerateSettingsFile() = 0;

	virtual void SaveSettingsFile() = 0;

	virtual TTypedTree<std::string>* DisplayMenu() = 0;

	virtual void DisplaySettings(const std::string& displayCategory) = 0;
};