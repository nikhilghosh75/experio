#pragma once
#include "ProjectSettingModule.h"
#include <vector>

class ProjectSettings
{
	static std::vector<ProjectSettingModule*> settingModules;

	friend class SettingsView;
public:
	static void Initialize();

	static void AddSettingsModule(ProjectSettingModule* settings);

	static void SaveAll();

	static void Shutdown();
};