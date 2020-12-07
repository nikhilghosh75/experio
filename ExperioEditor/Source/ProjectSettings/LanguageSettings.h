#pragma once

#include "ProjectSettingModule.h"

class LanguageSettings : public ProjectSettingModule
{
public:
	static LanguageSettings* languageSettings;

	uint8_t cppVersion;
	uint16_t glslVersion;

	float showAfterCompileTime = 3.f;

	std::vector<std::string> cppIncludePaths;

	LanguageSettings();

	virtual void ReadFromTable(toml::table table) override;

	virtual void GenerateSettingsFile() override;

	virtual void SaveSettingsFile() override;

	virtual TTypedTree<std::string>* DisplayMenu() override;

	virtual void DisplaySettings(const std::string& displayCategory) override;
};