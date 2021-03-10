#include "EditorSettings.h"
#include "../Core/EditorApplication.h"

EditorSettings* EditorSettings::settings;

EditorSettings::EditorSettings()
{
	this->settingsFile = "editor.pbconfig";
	settings = this;
}

void EditorSettings::ReadFromTable(toml::table table)
{
}

void EditorSettings::GenerateSettingsFile()
{
}

void EditorSettings::SaveSettingsFile()
{
}

TTypedTree<std::string>* EditorSettings::DisplayMenu()
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>("Editor");
	return tree;
}

void EditorSettings::DisplaySettings(const std::string& displayCategory)
{
	if (displayCategory == "Editor")
	{
		ImGui::Text("Editor Settings have not been implemented yet");
	}
}
