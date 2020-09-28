#include "EditorApplication.h"
#include <Windows.h>
#include <stdio.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "EditorWindow.h"
#include "Runtime/Core/Window.h"
#include "../Framework/ValueLoader.h"
#include "../Test Modules/TestModule.h"
#include "Runtime/Framework/SceneLoader.h"
#include "Runtime/Framework/Project.h"
#include "../Framework/EditorProject.h"

std::string projectName = "Experio Editor";

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

	// TEMP
	LoadProject("C:/Users/debgh/source/repos/project-bloo/bin/x64/Debug/Demo Project/Demo Project.dll");
	modules.push_back(new TestModule());

	EditorProject::TempSetup();
	bool sceneLoadedSuccess;
	// loader.CallFunction<bool, BOOLSTRINGINTPROC, std::string, int>("LoadScene", sceneLoadedSuccess, "C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Scenes/TestScene.pbscene", 0);

	while (EditorWindow::isActive)
	{
		EditorWindow::BeginFrame();
		// loader.CallFunction("Update");
		RenderModules();
		EditorWindow::EndFrame();
	}

	EditorWindow::CloseWindow();

	loader.UnloadDll();
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
		ImGui::Begin(("Module " + std::to_string(i)).c_str());
		modules[i]->Display();
		ImGui::End();
	}
}
