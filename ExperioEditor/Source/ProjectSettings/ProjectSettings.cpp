#include "ProjectSettings.h"
#include "LanguageSettings.h"
#include "RenderingSettings.h"
#include "SettingsView.h"
#include "../Core/EditorApplication.h"
#include <fstream>

std::vector<ProjectSettingModule*> ProjectSettings::settingModules;

void ProjectSettings::Initialize()
{
	AddSettingsModule(new LanguageSettings());
	AddSettingsModule(new RenderingSettings());
}

void ProjectSettings::AddSettingsModule(ProjectSettingModule * settings)
{
	std::string filePath = EditorApplication::configFilePath + "/" + settings->settingsFile;
	std::ifstream inFile(filePath);
	if (inFile.fail())
	{
		settings->GenerateSettingsFile();
	}
	else
	{
		toml::table table = toml::parse_file(filePath);
		settings->ReadFromTable(table);
	}
	settingModules.push_back(settings);

	SettingsView::instance->GenerateSettingMenuTree();
}

void ProjectSettings::Shutdown()
{
	for (size_t i = 0; i < settingModules.size(); i++)
	{
		settingModules[i]->SaveSettingsFile();
		delete settingModules[i];
	}
}
