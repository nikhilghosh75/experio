#include "BuildSettings.h"
#include "../Core/EditorApplication.h"
#include <fstream>

BuildSettings* BuildSettings::settings;

BuildSettings::BuildSettings()
{
	this->settingsFile = "build.pbconfig";
	settings = this;
}

void BuildSettings::ReadFromTable(toml::table table)
{
	this->convertFonts = table["Conversions"]["ConvertFonts"].value_or(true);
	this->convertMeshes = table["Conversions"]["ConvertMeshes"].value_or(true);
	this->convertScenes = table["Conversions"]["ConvertScenes"].value_or(true);
}

void BuildSettings::GenerateSettingsFile()
{
	toml::table table;

	toml::table conversionTable;
	conversionTable.insert("ConvertFonts", true);
	conversionTable.insert("ConvertMeshes", true);
	conversionTable.insert("ConvertScenes", true);

	table.insert("Conversions", conversionTable);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

void BuildSettings::SaveSettingsFile()
{
	toml::table table;

	toml::table conversionTable;
	conversionTable.insert("ConvertFonts", this->convertFonts);
	conversionTable.insert("ConvertMeshes", this->convertMeshes);
	conversionTable.insert("ConvertScenes", this->convertScenes);

	table.insert("Conversions", conversionTable);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

TTypedTree<std::string>* BuildSettings::DisplayMenu()
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>("Build");
	tree->AddChildToRoot("Conversions");

	return tree;
}

void BuildSettings::DisplaySettings(const std::string & displayCategory)
{
	if (displayCategory == "Build")
	{
		if (ImGui::TreeNodeEx("Conversions"))
		{
			DisplaySettings("Conversions");
			ImGui::TreePop();
		}
	}
	else if (displayCategory == "Conversions")
	{
		ImGui::Checkbox("Convert Fonts", &this->convertFonts);
		ImGui::Checkbox("Convert Meshes", &this->convertMeshes);
		ImGui::Checkbox("Convert Scenes", &this->convertScenes);
	}
}

