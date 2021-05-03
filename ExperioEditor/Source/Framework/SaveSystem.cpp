#include "SaveSystem.h"
#include "PlaySystem.h"
#include "SceneSaver.h"
#include "ValueSaver.h"
#include "../Core/EditorApplication.h"
#include "../Materials/MaterialEditor.h"
#include "../AssetViewers/LayerEditor.h"
#include "../AssetViewers/TagEditor.h"

std::vector<FSaveableAsset> SaveSystem::currentlyOpenAssets;
std::vector<bool> SaveSystem::shouldSaveAssets;

bool shouldOpenThisFrame = false;

ImVec4 SaveSystem::AssetTypeToColor(ESaveableAssetType assetType)
{
	switch (assetType)
	{
	case ESaveableAssetType::Scene: return ImVec4(147.f / 255.f, 1.f, 66.f / 255.f, 1.f);
	case ESaveableAssetType::Material: return ImVec4(129.f / 255.f, 66.f / 255.f, 1.f, 1.f);
	case ESaveableAssetType::Value: return ImVec4(0.88f, 0.88f, 0.88f, 1.f);
	}
	return ImVec4();
}

char* SaveSystem::AssetTypeToString(ESaveableAssetType assetType)
{
	switch (assetType)
	{
	case ESaveableAssetType::Scene: return "Scene";
	case ESaveableAssetType::Material: return "Material";
	case ESaveableAssetType::Value: return "Value";
	}
	return "None";
}

void SaveSystem::SaveAssetOfType(ESaveableAssetType assetType)
{
	switch (assetType)
	{
	case ESaveableAssetType::Scene: SaveScene(); break;
	case ESaveableAssetType::Material: SaveMaterial(); break;
	case ESaveableAssetType::Value: SaveValues(); break;
	}
}

void SaveSystem::SaveAll()
{
	SaveScene();
	SaveMaterial();
	SaveValues();
}

void SaveSystem::SaveScene()
{
	if (PlaySystem::GetPlaySystemState() == EPlaySystemState::NotPlaying)
	{
		SceneSaver::SaveScene(0, EditorApplication::currentScenePath);
	}
}

void SaveSystem::SaveMaterial()
{
	if (MaterialEditor::materialEditor == nullptr)
	{
		MaterialEditor::materialEditor->SaveMaterial();
	}
}

void SaveSystem::SaveValues()
{
	ValueSaver::SaveValues();
}

std::vector<FSaveableAsset> SaveSystem::GetCurrentlyOpenAssets()
{
	std::vector<FSaveableAsset> assets;

	assets.emplace_back(ESaveableAssetType::Scene, EditorApplication::currentScenePath);

	if (MaterialEditor::materialEditor != nullptr)
		assets.emplace_back(ESaveableAssetType::Material, MaterialEditor::materialEditor->GetCurrentFilepath());

	if (LayerEditor::layerEditor != nullptr)
		assets.emplace_back(ESaveableAssetType::Value, EditorApplication::configFilePath + "/layers.pbvalues");

	if(TagEditor::tagEditor != nullptr)
		assets.emplace_back(ESaveableAssetType::Value, EditorApplication::configFilePath + "/tags.pbvalues");

	return assets;
}

void SaveSystem::OpenSaveSelectedScreen()
{
	shouldOpenThisFrame = true;
}

void SaveSystem::DisplaySaveSelectedScreen()
{
	if (shouldOpenThisFrame)
	{
		ImGui::OpenPopup("Save Selected");
		currentlyOpenAssets = GetCurrentlyOpenAssets();
		shouldSaveAssets.resize(currentlyOpenAssets.size());
		std::fill(shouldSaveAssets.begin(), shouldSaveAssets.end(), true);
		shouldOpenThisFrame = false;
	}

	if (ImGui::BeginPopupModal("Save Selected", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		for (size_t i = 0; i < shouldSaveAssets.size(); i++)
		{
			bool shouldSaveAsset = shouldSaveAssets[i];
			ImGui::Checkbox(("##" + std::to_string(i)).c_str(), &shouldSaveAsset);
			shouldSaveAssets[i] = shouldSaveAsset;
			ImGui::SameLine();
			ImGui::Text(currentlyOpenAssets[i].filepath.c_str());
			ImGui::SameLine();
			ESaveableAssetType assetType = currentlyOpenAssets[i].type;
			ImGui::TextColored(AssetTypeToColor(assetType), AssetTypeToString(assetType));
		}

		if (ImGui::Button("Save Selected"))
		{
			for (size_t i = 0; i < shouldSaveAssets.size(); i++)
			{
				if (shouldSaveAssets[i])
				{
					SaveAssetOfType(currentlyOpenAssets[i].type);
				}
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

FSaveableAsset::FSaveableAsset()
{
	this->type = ESaveableAssetType::None;
	this->filepath = "";
}

FSaveableAsset::FSaveableAsset(ESaveableAssetType type)
{
	this->type = type;
	this->filepath = "";
}

FSaveableAsset::FSaveableAsset(ESaveableAssetType type, std::string filepath)
{
	this->type = type;
	this->filepath = filepath;
}
