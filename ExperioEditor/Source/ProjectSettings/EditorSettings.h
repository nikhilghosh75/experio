#pragma once

#include "ProjectSettingModule.h"

class EditorSettings : public ProjectSettingModule
{
public:
	static EditorSettings* settings;

	EditorSettings();

	virtual void ReadFromTable(toml::table table) override;

	virtual void GenerateSettingsFile() override;

	virtual void SaveSettingsFile() override;

	virtual TTypedTree<std::string>* DisplayMenu() override;

	virtual void DisplaySettings(const std::string& displayCategory) override;
};