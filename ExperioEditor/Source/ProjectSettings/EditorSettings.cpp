#include "EditorSettings.h"
#include "Runtime/Math/LMath.h"
#include "../Core/EditorApplication.h"
#include <fstream>
#include <string>

EditorSettings* EditorSettings::settings;

static const float validAutosaveTimes[] = { 60, 120, 180, 240, 300, 600, 1200, 1800, 3600, 7200 };
static const std::string validAutosaveTimeStrs[] = 
	{ "Every minute", "Every two minutes", "Every three minutes", "Every four minutes", 
	"Every five minutes", "Every ten minutes", "Every twenty minutes", "Every thirty minutes", 
	"Every hour", "Every two hours"};

#define PB_AUTOSAVE_TIMES 10

EditorSettings::EditorSettings()
{
	this->settingsFile = "editor.pbconfig";
	settings = this;
}

void EditorSettings::ReadFromTable(toml::table table)
{
	this->editorAutosaveEnabled = table["Autosave"]["Enabled"].value_or(false);
	this->editorAutosaveTime = table["Autosave"]["Time"].value_or(240);
	this->autosaveFlowcharts = table["Autosave"]["Flowcharts"].value_or(false);
	this->autosaveMaterials = table["Autosave"]["Materials"].value_or(false);
	this->autosaveScenes = table["Autosave"]["Scenes"].value_or(false);
	this->autosaveValues = table["Autosave"]["Values"].value_or(true);
}

void EditorSettings::GenerateSettingsFile()
{
	toml::table table;

	toml::table autosave;
	autosave.insert("Enabled", false);
	autosave.insert("Time", 240);
	autosave.insert("Flowcharts", false);
	autosave.insert("Materials", false);
	autosave.insert("Scenes", false);
	autosave.insert("Values", false);
	table.insert("Autosave", autosave);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

void EditorSettings::SaveSettingsFile()
{
	toml::table table;

	toml::table autosave;
	autosave.insert("Enabled", editorAutosaveEnabled);
	autosave.insert("Time", editorAutosaveTime);
	autosave.insert("Flowcharts", autosaveFlowcharts);
	autosave.insert("Materials", autosaveMaterials);
	autosave.insert("Scenes", autosaveScenes);
	autosave.insert("Values", autosaveValues);
	table.insert("Autosave", autosave);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

TTypedTree<std::string>* EditorSettings::DisplayMenu()
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>("Editor");
	tree->AddChildToRoot("Autosave");
	return tree;
}

void EditorSettings::DisplaySettings(const std::string& displayCategory)
{
	if (displayCategory == "Editor")
	{
		if (ImGui::TreeNodeEx("Autosave"))
		{
			DisplaySettings("Autosave");
			ImGui::TreePop();
		}
		return;
	}

	if (displayCategory == "Autosave")
	{
		ImGui::Checkbox("Enable Autosave", &editorAutosaveEnabled);
		if (editorAutosaveEnabled)
		{
			// Autosave Frequency
			size_t autosaveTimeIndex = 0;
			for (size_t i = 0; i < PB_AUTOSAVE_TIMES; i++)
			{
				if (LMath::ApproxEquals(editorAutosaveTime, validAutosaveTimes[i], 0.01f))
					autosaveTimeIndex = i;
			}

			if (ImGui::BeginCombo("Autosave Frequency", validAutosaveTimeStrs[autosaveTimeIndex].c_str()))
			{
				for (size_t i = 0; i < PB_AUTOSAVE_TIMES; i++)
				{
					if (ImGui::Selectable(validAutosaveTimeStrs[i].c_str(), i == autosaveTimeIndex))
					{
						editorAutosaveTime = validAutosaveTimes[i];
					}
				}
				ImGui::EndCombo();
			}

			// File types to autosave
			ImGui::Checkbox("Autosave Flowcharts", &autosaveFlowcharts);
			ImGui::Checkbox("Autosave Materials", &autosaveMaterials);
			ImGui::Checkbox("Autosave Scenes", &autosaveScenes);
			ImGui::Checkbox("Autosave Values", &autosaveValues);
		}
	}
}
