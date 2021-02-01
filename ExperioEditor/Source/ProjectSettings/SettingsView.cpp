#include "SettingsView.h"
#include "ProjectSettings.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "imgui.h"

SettingsView* SettingsView::instance;

SettingsView::SettingsView()
{
	this->name = "Project Settings";
	this->category = EEditorModuleCategory::Viewer;

	instance = this;

	GenerateSettingMenuTree();
}

SettingsView::~SettingsView()
{
	for (size_t i = 0; i < this->settingMenuTrees.size(); i++)
	{
		delete settingMenuTrees[i];
	}
}

void SettingsView::Display()
{
	ImGui::BeginChild("left pane", ImVec2(150, 0), true);
	for (size_t i = 0; i < settingMenuTrees.size(); i++)
	{
		LImGui::DisplaySubTree(settingMenuTrees[i]->GetRoot(), "SettingsTree", selectedSetting);
	}
	ImGui::EndChild();

	std::vector<ProjectSettingModule*>& modules = ProjectSettings::settingModules;
	ImGui::SameLine();

	ImGui::BeginGroup();
	ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
	if (selectedSetting == "None")
	{
		ImGui::Text("No Settings Selected");
	}
	else
	{
		for (size_t i = 0; i < modules.size(); i++)
		{
			modules[i]->DisplaySettings(selectedSetting);
		}
	}
	ImGui::EndChild();
	ImGui::EndGroup();
}

void SettingsView::GenerateSettingMenuTree()
{
	for (size_t i = 0; i < this->settingMenuTrees.size(); i++)
	{
		if (this->settingMenuTrees[i] != nullptr)
		{
			delete this->settingMenuTrees[i];
		}
	}

	this->settingMenuTrees.clear();

	std::vector<ProjectSettingModule*>& modules = ProjectSettings::settingModules;

	for (size_t i = 0; i < modules.size(); i++)
	{
		this->settingMenuTrees.push_back(modules[i]->DisplayMenu());
	}
}
