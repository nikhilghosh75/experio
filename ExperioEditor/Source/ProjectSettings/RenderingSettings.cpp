#include "RenderingSettings.h"
#include "../Core/EditorApplication.h"
#include <fstream>

RenderingSettings::RenderingSettings()
{
	this->settingsFile = "rendering.pbconfig";

}

void RenderingSettings::ReadFromTable(toml::table table)
{
	this->particleTimestep = table["Particles"]["Timestep"].value_or(1 / 60);
}

void RenderingSettings::GenerateSettingsFile()
{
	toml::table table;

	toml::table particleTable;
	particleTable.insert("Timestep", 1 / 60);
	table.insert("Particles", particleTable);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

void RenderingSettings::SaveSettingsFile()
{
	toml::table table;

	toml::table particleTable;
	particleTable.insert("Timestep", this->particleTimestep);
	table.insert("Particles", particleTable);

	std::ofstream outFile(EditorApplication::configFilePath + "/" + this->settingsFile);
	outFile << table;
}

TTypedTree<std::string>* RenderingSettings::DisplayMenu()
{
	TTypedTree<std::string>* tree = new TTypedTree<std::string>("Rendering");
	tree->AddChildToRoot("Particles");

	return tree;
}

void RenderingSettings::DisplaySettings(const std::string & displayCategory)
{
	if (displayCategory == "Rendering")
	{
		if (ImGui::TreeNode("Particles"))
		{
			DisplaySettings("Particles");
			ImGui::TreePop();
		}
	}
	if (displayCategory == "Particles")
	{
		ImGui::DragFloat("Particle Timestep", &this->particleTimestep, 0.001f, 0.0005f, 0.04f);
	}
}
