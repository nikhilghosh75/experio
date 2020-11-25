#include "LanguageSettings.h"
#include "../Core/EditorApplication.h"
#include "ThirdParty\toml++\toml_conversions.h"
#include <fstream>

constexpr uint8_t validCPPVersions[] = { 17, 20 };
constexpr uint8_t numCPPVersions = 2;
constexpr uint8_t firstExperimentalCPPVersion = 20;

LanguageSettings::LanguageSettings()
{
	this->settingsFile = "languages.pbconfig";
}

void LanguageSettings::ReadFromTable(toml::table table)
{
	this->cppVersion = table["CPP"]["Version"].value_or(17);
	this->cppIncludePaths = TomlToVector<std::string>(table["CPP"]["IncludePaths"].as_array());

	this->glslVersion = table["GLSL"]["Version"].value_or(460);
}

void LanguageSettings::GenerateSettingsFile()
{
	toml::table table;

	toml::table cppTable;
	cppTable.insert("Version", 17);
	cppTable.insert("IncludePaths", toml::array{ "(SolutionDir)Experio\Source", "(SolutionDir)Dependencies\GLEW\include", "(SolutionDir)Dependencies\imgui" });
	table.insert("CPP", cppTable);

	toml::table glslTable;
	glslTable.insert("Version", 460);
	table.insert("GLSL", glslTable);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

void LanguageSettings::SaveSettingsFile()
{
	toml::table table;

	toml::table cppTable;
	cppTable.insert("Version", this->cppVersion);
	cppTable.insert("IncludePaths", VectorToToml(this->cppIncludePaths));
	table.insert("CPP", cppTable);

	toml::table glslTable;
	glslTable.insert("Version", this->glslVersion);
	table.insert("GLSL", glslTable);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

TTypedTree<std::string>* LanguageSettings::DisplayMenu()
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>("Language");
	tree->AddChildToRoot("C++");
	tree->AddChildToRoot("GLSL");

	return tree;
}

void LanguageSettings::DisplaySettings(const std::string & displayCategory)
{
	if (displayCategory == "Language")
	{
		if (ImGui::TreeNodeEx("C++"))
		{
			DisplaySettings("C++");
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("GLSL"))
		{
			DisplaySettings("GLSL");
			ImGui::TreePop();
		}
		return;
	}
	
	if (displayCategory == "C++")
	{
		// Version
		uint8_t experimentalCPPVersion = 0;
		if (ImGui::BeginCombo("Version", std::to_string(this->cppVersion).c_str()))
		{
			for (size_t i = 0; i < numCPPVersions; i++)
			{
				bool isSelected = this->cppVersion == validCPPVersions[i];
				if (ImGui::Selectable(std::to_string(validCPPVersions[i]).c_str(), &isSelected))
				{
					if (validCPPVersions[i] >= firstExperimentalCPPVersion && validCPPVersions[i] != this->cppVersion)
					{
						ImGui::OpenPopup("Switch To Experimental C++?");
						experimentalCPPVersion = validCPPVersions[i];
					}
					this->cppVersion = validCPPVersions[i];
				}
			}
			ImGui::EndCombo();
		}
		if (ImGui::BeginPopupModal("Switch To Experimental C++?"))
		{
			ImGui::Text("This is a dangerous operation, as this version of C++ is not fully supported by Experio");
			if (ImGui::ColorButton("Cancel", ImVec4(1, 0, 0, 1)))
			{
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::ColorButton("Switch", ImVec4(0, 1, 0, 1)))
			{
				this->cppVersion = experimentalCPPVersion;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		return;
	}
}
