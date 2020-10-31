#include "EditorApplication.h"
#include <Windows.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "imgui_demo.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "EditorWindow.h"
#include "../Framework/ValueLoader.h"
#include "Runtime/Framework/SceneLoader.h"
#include "../Framework/EditorProject.h"
#include "../SceneView/SceneView.h"
#include "../FileView/FileView.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "Runtime/Debug/TempProfiler.h"
#include "../CodeParser/CodeProject.h"
#include "../CodeParser/CodeProjectGenerator.h"
#include "../Inspector/Inspector.h"
#include "../Framework/SceneSaver.h"

std::vector<EditorModule*> EditorApplication::modules;
DllLoader EditorApplication::loader;

std::string EditorApplication::assetsFilePath;
std::string EditorApplication::configFilePath;
std::string EditorApplication::scriptsFilePath;

std::string EditorApplication::standardAssetsFilePath;

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

void EditorApplication::Setup()
{
	PROFILE_SCOPE("Editor Setup");
	EditorWindow::InitializeWindow();
	Project::inEditor = true;

	modules.push_back(new SceneView());
	modules.push_back(new FileView());
	modules.push_back(new SceneHierarchy());
	modules.push_back(new Inspector());

	TempSetup();

	EditorProject::TempSetup();
	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Scenes/TestScene.pbscene", 0);
	Scene::Activate(0);

	Project::StartGame();
}

void EditorApplication::Run()
{
	TempProfiler* profiler = new TempProfiler("Code Parsers");
	FCodeProjectOptions options;
	options.codingLanguage = ECodingLanguage::CPlusPlus;
	options.generateInstantly = true;
	// CodeProject project("C:/Users/debgh/source/repos/project-bloo/Experio/Source/Runtime", options);
	delete profiler;

	while (EditorWindow::isActive)
	{
		PROFILE_SCOPE("Editor Loop");
		
		BeginFrame();
		RenderModules();
		// bool temp = true;
		// ImGui::ShowDemoWindow(&temp);
		EndFrame();

	}

	EditorWindow::CloseWindow();
}

void EditorApplication::Shutdown()
{
	Project::EndGame();
	Scene::UnloadAllScenes();
}

void EditorApplication::SetBeginFrameCallback(void(*callback)(float))
{
	beginFrameCallback = callback;
}

void EditorApplication::SetEndFrameCallback(void(*callback)(float))
{
	endFrameCallback = callback;
}

void EditorApplication::LoadProject(std::string dllFilePath)
{
	loader.LoadDll(dllFilePath);
	loader.CallFunction("SetupProject");
	loader.CallVoidFunction<VOIDHWNDPROC, HWND>("SetupGraphics", EditorWindow::GetHWND());
}

std::string EditorApplication::GetShortenedFilePath(std::string & fullFilePath)
{
	size_t foundIndex;

	// Compare with Assets Filepath
	foundIndex = fullFilePath.find(assetsFilePath);
	if (foundIndex != std::string::npos) return fullFilePath.substr(assetsFilePath.size());

	foundIndex = fullFilePath.find(configFilePath);
	if (foundIndex != std::string::npos) return "?Config?" + fullFilePath.substr(configFilePath.size());

	foundIndex = fullFilePath.find(scriptsFilePath);
	if (foundIndex != std::string::npos) return "?Source?" + fullFilePath.substr(scriptsFilePath.size());

	foundIndex = fullFilePath.find(standardAssetsFilePath);
	if (foundIndex != std::string::npos) return "?Standard?" + fullFilePath.substr(standardAssetsFilePath.size());

	return fullFilePath;
}

void EditorApplication::TempSetup()
{
	assetsFilePath = "C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/";
	configFilePath = "C:/Users/debgh/source/repos/project-bloo/Demo Project/Config/";
	scriptsFilePath = "C:/Users/debgh/source/repos/project-bloo/Demo Project/Source/";

	standardAssetsFilePath = "C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard";
}

void EditorApplication::BeginFrame()
{
	EditorWindow::BeginFrame();
	Project::BeginFrame();

	if (beginFrameCallback != nullptr)
	{
		beginFrameCallback(GameTime::deltaTime);
	}
}

void EditorApplication::EndFrame()
{
	if (endFrameCallback != nullptr)
	{
		endFrameCallback(GameTime::deltaTime);
	}

	EditorWindow::EndFrame();
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
