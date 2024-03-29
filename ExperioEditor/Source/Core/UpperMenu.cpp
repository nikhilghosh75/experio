#include "UpperMenu.h"
#include "EditorApplication.h"
#include "EditorWindow.h"
#include "FileDialog.h"
#include "../AssetViewers/LayerEditor.h"
#include "../AssetViewers/TagEditor.h"
#include "../BuildSystem/BuildSystem.h"
#include "../FileView/FileView.h"
#include "../Flowcharts/FlowchartViewer.h"
#include "../Framework/AdminTools.h"
#include "../Framework/CreateMenu.h"
#include "../Framework/EditorProject.h"
#include "../Framework/ImportSystem.h"
#include "../Framework/MetaSystem.h"
#include "../Framework/PlaySystem.h"
#include "../Framework/SaveSystem.h"
#include "../Framework/SceneSaver.h"
#include "../Framework/UndoSystem.h"
#include "../Profilers/InputDebugger.h"
#include "../Profilers/MemoryProfiler.h"
#include "../Profilers/TimeProfiler.h"
#include "../ProjectSettings/ProjectSettings.h"
#include "../ProjectSettings/SettingsView.h"
#include "../Terminal/Terminal.h"
#include "../Testing/TestRunner.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Framework/SceneLoader.h"
#include "imgui.h"

using namespace ExperioEditor;

extern void RCCCompileProject();

void UpperMenu::CreateUpperMenu()
{
	if (ImGui::BeginMenuBar())
	{
		CreateFileMenu();
		CreateEditMenu();
		CreateAssetMenu();
		CreateProjectMenu();
		CreateWindowMenu();

		ImGui::EndMenuBar();
	}
}

void UpperMenu::CreateFileMenu()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("New Scene"))
		{
			SaveSystem::SaveScene();
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
			SaveSystem::SaveScene();
		}
		if (ImGui::MenuItem("Save Scene As"))
		{
			FFileDialogInfo dialogInfo = FileDialog::SaveFile("Experio Scene (*.pbscene)\0*.pbscene\0");
			if (dialogInfo.IsValid())
			{
				SceneSaver::SaveScene(0, dialogInfo.filename + ".pbscene");
			}
		}
		if (ImGui::MenuItem("Save Selected"))
		{
			SaveSystem::OpenSaveSelectedScreen();
		}
		if (ImGui::MenuItem("Save All"))
		{
			SaveSystem::SaveAll();
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Close"))
		{
			EditorWindow::CloseWindow();
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Build"))
		{
			FFileDialogInfo dialogInfo = FileDialog::OpenFolder();
			if (dialogInfo.IsValid())
			{
				BuildSystem::StartBuildForWindows(dialogInfo.filename, BuildSystem::DefaultWindowsBuildSettings());
			}
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Compile Project"))
		{
			RCCCompileProject();
		}

		ImGui::EndMenu();
	}
}

void UpperMenu::CreateEditMenu()
{
	if (ImGui::BeginMenu("Edit"))
	{
		if (ImGui::MenuItem("Undo"))
		{
			UndoSystem::Undo();
		}
		if (ImGui::MenuItem("Redo"))
		{
			UndoSystem::Redo();
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Play"))
		{
			PlaySystem::StartGame();
		}
		if (ImGui::MenuItem("Pause"))
		{
			PlaySystem::PauseGame();
		}
		if (ImGui::MenuItem("Stop"))
		{
			PlaySystem::StopGame();
		}

		ImGui::EndMenu();
	}
}

void UpperMenu::CreateAssetMenu()
{
	if (ImGui::BeginMenu("Assets"))
	{
		if (ImGui::MenuItem("Import"))
		{
			std::vector<FFileDialogInfo> dialogs = FileDialog::OpenMultipleFiles(nullptr);

			for (size_t i = 0; i < dialogs.size(); i++)
			{
				ImportSystem::Import(dialogs[i].filename, FileView::fileView->GetSelectedFilepath());
			}
		}
		ImGui::Separator();
		if (ImGui::MenuItem("Refresh"))
		{
			FileView::fileView->Reload();
		}
		if (ImGui::MenuItem("Regenerate Meta Files"))
		{
			MetaSystem::FixMetafiles();
		}

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

void UpperMenu::CreateWindowMenu()
{
	if (ImGui::BeginMenu("Window"))
	{
		if (ImGui::BeginMenu("Layout"))
		{
			if (ImGui::MenuItem("Default"))
			{
				EditorProject::QueueSetLayout(EEditorLayout::Default);
			}
			if (ImGui::MenuItem("Tall"))
			{
				EditorProject::QueueSetLayout(EEditorLayout::Tall);
			}
			if (ImGui::MenuItem("Wide"))
			{
				EditorProject::QueueSetLayout(EEditorLayout::Wide);
			}
			ImGui::EndMenu();
		}
		ImGui::Separator();
		if (ImGui::BeginMenu("Profiling"))
		{
			if (ImGui::MenuItem("Memory Profiler"))
			{
				EditorApplication::AddModule(new MemoryProfiler());
			}
			if (ImGui::MenuItem("Time Profiler"))
			{
				EditorApplication::AddModule(new TimeProfiler());
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Input Debugger"))
			{
				EditorApplication::AddModule(new InputDebugger());
			}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Test Runner"))
		{
			EditorApplication::AddModule(new TestRunner());
		}
		if (ImGui::MenuItem("Terminal"))
		{
			EditorApplication::AddModule(new Terminal());
		}
		if (ImGui::MenuItem("Admin"))
		{
			EditorApplication::AddModule(new AdminTools());
		}
		if (ImGui::MenuItem("Flowchart"))
		{
			EditorApplication::AddModule(new FlowchartViewer());
		}
		ImGui::EndMenu();
	}
}
