#include "EditorApplication.h"
#include <Windows.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "EditorWindow.h"
#include "../Framework/ValueLoader.h"
#include "../Test Modules/TestModule.h"
#include "Runtime/Framework/SceneLoader.h"
#include "../Framework/EditorProject.h"
#include "../SceneView/SceneView.h"
#include "../FileView/FileView.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "Runtime/Debug/TempProfiler.h"

std::vector<EditorModule*> EditorApplication::modules;
DllLoader EditorApplication::loader;

EditorApplication::EditorApplication()
{
}

EditorApplication::~EditorApplication()
{
	for (int i = 0; i < modules.size(); i++)
	{
		delete modules[i];
	}
}

void EditorApplication::Run()
{
	EditorWindow::InitializeWindow();
	Project::inEditor = true;

	// modules.push_back(new TestModule());
	modules.push_back(new SceneView());
	modules.push_back(new FileView());
	modules.push_back(new SceneHierarchy());

	EditorProject::TempSetup();
	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Scenes/TestScene.pbscene", 0);
	Scene::Activate(0);

	Project::StartGame();

	while (EditorWindow::isActive)
	{
		PROFILE_SCOPE("Editor Loop");
		EditorWindow::BeginFrame();
		Project::BeginFrame();
		RenderModules();

		EditorWindow::EndFrame();
	}

	EditorWindow::CloseWindow();
}

void EditorApplication::LoadProject(std::string dllFilePath)
{
	loader.LoadDll(dllFilePath);
	loader.CallFunction("SetupProject");
	loader.CallVoidFunction<VOIDHWNDPROC, HWND>("SetupGraphics", EditorWindow::GetHWND());
}

void EditorApplication::RenderModules()
{
	for (int i = 0; i < modules.size(); i++)
	{
		ImGui::Begin(modules[i]->name.c_str());

		if (ImGui::IsWindowFocused())
		{
			modules[i]->HandleInput();
		}

		modules[i]->Display();
		ImGui::End();
	}
}
