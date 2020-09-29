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
#include "Runtime/Rendering/Renderer.h"
#include "Runtime/Camera/AdditionalCameras.h"
#include "../SceneView/SceneView.h"

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

	modules.push_back(new TestModule());
	modules.push_back(new SceneView());

	EditorProject::TempSetup();
	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Scenes/TestScene.pbscene", 0);
	Scene::Activate(0);

	while (EditorWindow::isActive)
	{
		EditorWindow::BeginFrame();

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
		ImGui::Begin(("Module " + std::to_string(i)).c_str());
		modules[i]->Display();
		ImGui::End();
	}
}
