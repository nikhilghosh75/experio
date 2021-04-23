#include "SaveSystem.h"
#include "PlaySystem.h"
#include "SceneSaver.h"
#include "ValueSaver.h"
#include "../Core/EditorApplication.h"
#include "../Materials/MaterialEditor.h"
#include "../AssetViewers/LayerEditor.h"
#include "../AssetViewers/TagEditor.h"

std::vector<FSaveableAsset> SaveSystem::currentlyOpenAssets;

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
	ImGui::OpenPopup("Save Selected");
}

void SaveSystem::DisplaySaveSelectedScreen()
{
	if (ImGui::BeginPopupModal("Save Selected", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{

		if (ImGui::Button("Save Selected"))
		{

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
