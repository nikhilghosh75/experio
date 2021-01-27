#pragma once

#include "ProjectSettingModule.h"

class BuildSettings : public ProjectSettingModule
{
public:
	static BuildSettings* settings;

	bool convertFonts;
	bool convertMeshes;
	bool convertScenes;

	BuildSettings();

	virtual void ReadFromTable(toml::table table) override;

	virtual void GenerateSettingsFile() override;

	virtual void SaveSettingsFile() override;

	virtual TTypedTree<std::string>* DisplayMenu() override;

	virtual void DisplaySettings(const std::string& displayCategory) override;
};