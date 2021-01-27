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
#include "../BuildSystem/CodeGenerator.h"
#include "../CodeParser/CodeProjectGenerator.h"
#include "../ComponentEditor/GeneratedEditor.h"
#include "../Console/Console.h"
#include "../FileView/FileView.h"
#include "../Framework/Compilation/CompilationParser.h"
#include "../Framework/CreateMenu.h"
#include "../Framework/EditorProject.h"
#include "../Framework/EditorShortcuts.h"
#include "../Framework/ImportSystem.h"
#include "../Framework/NotificationSystem.h"
#include "../Framework/SceneSaver.h"
#include "../Framework/ValueLoader.h"
#include "../GameView/GameView.h"
#include "../Inspector/Inspector.h"
#include "../ProjectSettings/ProjectSettings.h"
#include "../ProjectSettings/SettingsView.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../SceneView/SceneView.h"
#include "Runtime/Containers/TBinarySearchTree.h"
#include "Runtime/Framework/SceneLoader.h"

std::vector<EditorModule*> EditorApplication::modules;
DllLoader EditorApplication::loader;

std::string EditorApplication::assetsFilePath;
std::string EditorApplication::binariesFilePath;
std::string EditorApplication::configFilePath;
std::string EditorApplication::editorFilePath;
std::string EditorApplication::generatedFilePath;
std::string EditorApplication::sourceFilePath;

std::string EditorApplication::defaultScenePath;

std::string EditorApplication::currentScenePath;

std::string EditorApplication::experioFilePath;
std::string EditorApplication::experioEditorFilePath;
std::string EditorApplication::experioDependenciesFilePath;
std::string EditorApplication::experioBinariesFilePath;

std::string EditorApplication::standardAssetsFilePath = "C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard";

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

void EditorApplication::Setup(const std::string& projectFilepath)
{
	// PROFILE_SCOPE("Editor Setup");
	EditorWindow::InitializeWindow();
	Project::inEditor = true;

	EditorProject::ReadProjectFile(projectFilepath);
	EditorProject::ReadValueFiles();
	EditorProject::ReadUserFile("../user.pbuser");
	EditorProject::SetupRuntimeCompilation();
	EditorProject::TempSetup();

	currentScenePath = defaultScenePath;

	AddDefaultModules();

	ProjectSettings::Initialize();
	CreateMenu::Initialize();
	CompilationParser::Initialize();
	EditorShortcuts::Initialize();
	ImportSystem::Initialize();
}

void EditorApplication::LoadScenes()
{
	SceneLoader::LoadSceneFromFile(defaultScenePath, 0);
	Scene::Activate(0);
}

void EditorApplication::Run()
{
	CodeGenerator::GenerateAllFiles();

	Project::StartGame();

	while (EditorWindow::isActive)
	{
		// PROFILE_SCOPE("Editor Loop");
		
		BeginFrame();
		Update();
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

	ProjectSettings::Shutdown();
}

void EditorApplication::SetBeginFrameCallback(void(*callback)(float))
{
	beginFrameCallback = callback;
}

void EditorApplication::SetEndFrameCallback(void(*callback)(float))
{
	endFrameCallback = callback;
}

std::string EditorApplication::GetShortenedFilePath(std::string & fullFilePath)
{
	size_t foundIndex;

	// Compare with Assets Filepath
	foundIndex = fullFilePath.find(assetsFilePath);
	if (foundIndex != std::string::npos) return fullFilePath.substr(assetsFilePath.size());

	foundIndex = fullFilePath.find(configFilePath);
	if (foundIndex != std::string::npos) return "?Config?" + fullFilePath.substr(configFilePath.size());

	foundIndex = fullFilePath.find(sourceFilePath);
	if (foundIndex != std::string::npos) return "?Source?" + fullFilePath.substr(sourceFilePath.size());

	foundIndex = fullFilePath.find(standardAssetsFilePath);
	if (foundIndex != std::string::npos) return "?Standard?" + fullFilePath.substr(standardAssetsFilePath.size());

	return fullFilePath;
}

EditorModule * EditorApplication::AddModule(EditorModule * module)
{
	modules.push_back(module);
	return module;
}

void EditorApplication::AddDefaultModules()
{
	modules.push_back(new SceneView());
	modules.push_back(new FileView());
	modules.push_back(new SceneHierarchy());
	modules.push_back(new Inspector());
	modules.push_back(new GameView());
	// modules.push_back(new Console());

	modules.push_back(new SettingsView());
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

void EditorApplication::Update()
{
	RenderModules();
	NotificationSystem::RenderNotifications();
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

		if (ImGui::IsWindowFocused() || ImGui::IsWindowHovered())
		{
			modules[i]->HandleInput();
		}

		modules[i]->Display();
		ImGui::End();
	}
}
