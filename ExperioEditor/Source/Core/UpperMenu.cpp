#include "UpperMenu.h"
#include "EditorApplication.h"
#include "EditorWindow.h"
#include "FileDialog.h"
#include "../AssetViewers/LayerEditor.h"
#include "../AssetViewers/TagEditor.h"
#include "../Framework/CreateMenu.h"
#include "../Framework/SceneSaver.h"
#include "../Framework/ValueSaver.h"
#include "../ProjectSettings/ProjectSettings.h"
#include "../ProjectSettings/SettingsView.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Framework/SceneLoader.h"
#include "imgui.h"

void UpperMenu::CreateUpperMenu()
{
	if (ImGui::BeginMenuBar())
	{
		CreateFileMenu();
		CreateEditMenu();
		CreateProjectMenu();

		ImGui::EndMenuBar();
	}
}

void UpperMenu::CreateFileMenu()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New Scene"))
		{
			SceneSaver::SaveScene(0, EditorApplication::currentScenePath);
			Scene::UnloadAllScenes();
			Scene::LoadBlankScene(0);
		}
		if (ImGui::MenuItem("Open Scene"))
		{
			FFileDialogInfo dialogInfo = FileDialog::OpenFile("Experio Scene (*.pbscene)\0*.pbscene\0");
			if (dialogInfo.IsValid())
			{
				Scene::UnloadScene(0);
				SceneLoader::LoadSceneFromFile(dialogInfo.filename, 0);
			}
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Save Scene"))
		{
			SceneSaver::SaveScene(0, EditorApplication::currentScenePath);
		}
		if (ImGui::MenuItem("Save Scene As"))
		{
			FFileDialogInfo dialogInfo = FileDialog::SaveFile("Experio Scene (*.pbscene)\0*.pbscene\0");
			if (dialogInfo.IsValid())
			{
				SceneSaver::SaveScene(0, dialogInfo.filename + ".pbscene");
			}
		}
		if (ImGui::MenuItem("Save All"))
		{
			SaveAll();
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Close"))
		{
			EditorWindow::CloseWindow();
		}

		ImGui::EndMenu();
	}
}

void UpperMenu::CreateEditMenu()
{
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::Text("There are no items here yet");

		ImGui::EndMenu();
	}
}

void UpperMenu::CreateProjectMenu()
{
	if (ImGui::BeginMenu("Project"))
	{
		if (ImGui::MenuItem("Tags"))
		{
			EditorApplication::AddModule(new TagEditor());
		}
		if (ImGui::MenuItem("Layers"))
		{
			EditorApplication::AddModule(new LayerEditor());
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Project Settings"))
		{
			EditorApplication::AddModule(new SettingsView());
		}
		ImGui::EndMenu();
	}
}

void UpperMenu::SaveAll()
{
	SceneSaver::SaveScene(0, EditorApplication::currentScenePath);
	ValueSaver::SaveValues();
	ProjectSettings::SaveAll();
}
