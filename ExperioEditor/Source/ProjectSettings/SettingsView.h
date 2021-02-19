#pragma once
#include "../Core/EditorModule.h"
#include "ProjectSettingModule.h"
#include "Runtime/Containers/TTypedTree.h"
#include <string>

class SettingsView : public EditorModule
{
	std::vector<TTypedTree<std::string>*> settingMenuTrees;

	std::string selectedSetting = "None";
public:
	static SettingsView* instance;
	
	SettingsView();

	~SettingsView();

	virtual void Display() override;

	void GenerateSettingMenuTree();
};