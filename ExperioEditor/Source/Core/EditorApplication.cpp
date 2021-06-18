#include "EditorApplication.h"
#include <Windows.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "EditorWindow.h"
#include "../BuildSystem/CodeGenerator.h"
#include "../CodeParser/CodeProjectGenerator.h"
#include "../ComponentEditor/GeneratedEditor.h"
#include "../Console/Console.h"
#include "../FileView/FileView.h"
#include "../Framework/AssetManager.h"
#include "../Framework/Compilation/CompilationParser.h"
#include "../Framework/CreateMenu.h"
#include "../Framework/EditorProject.h"
#include "../Framework/EditorShortcuts.h"
#include "../Framework/ImportSystem.h"
#include "../Framework/NotificationSystem.h"
#include "../Framework/SceneSaver.h"
#include "../Framework/SaveSystem.h"
#include "../Framework/UndoSystem.h"
#include "../Framework/ValueLoader.h"
#include "../GameView/GameView.h"
#include "../Inspector/Inspector.h"
#include "../ProjectSettings/ProjectSettings.h"
#include "../ProjectSettings/SettingsView.h"
#include "../SceneHierarchy/SceneHierarchy.h"
#include "../SceneView/SceneView.h"
#include "../Terminal/Terminal.h"
#include "Runtime/Data/LStatistics.h"
#include "Runtime/Debug/Profiler.h"
#include "Runtime/Framework/Project.h"
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
	beginFrameCallback = nullptr;
	endFrameCallback = nullptr;
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
	EditorProject::SetProjectPaths();
	EditorProject::SetupRuntimeCompilation();
	EditorProject::SetLayout(EEditorLayout::Default);
	// EditorProject::Setup();
	EditorProject::TempSetupClasses();
	EditorProject::TempSetupMaterials();

	EditorProject::ReadComponents();
	EditorProject::FindComponents();

	currentScenePath = defaultScenePath;

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg].w = 1.f;

	AddDefaultModules();

	AssetManager::Populate();

	ProjectSettings::Initialize();

	CreateMenu::Initialize();
	CompilationParser::Initialize();
	EditorShortcuts::Initialize();
	ImportSystem::Initialize();
	NotificationSystem::Initialize();
	Terminal::Initialize();
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
		PROFILE_SCOPE("Editor Loop");
		
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
	ImportSystem::Shutdown();
	UndoSystem::FlushCommands();
}

void EditorApplication::SetBeginFrameCallback(void(*callback)(float))
{
	beginFrameCallback = callback;
}

void EditorApplication::SetEndFrameCallback(void(*callback)(float))
{
	endFrameCallback = callback;
}

std::string EditorApplication::GetShortenedFilePath(const std::string & fullFilePath)
{
	size_t foundIndex;

	// Compare with Assets Filepath
	foundIndex = fullFilePath.find(assetsFilePath);
	if (foundIndex != std::string::npos) return "?Assets?" + fullFilePath.substr(assetsFilePath.size());

	foundIndex = fullFilePath.find(configFilePath);
	if (foundIndex != std::string::npos) return "?Config?" + fullFilePath.substr(configFilePath.size());

	foundIndex = fullFilePath.find(sourceFilePath);
	if (foundIndex != std::string::npos) return "?Source?" + fullFilePath.substr(sourceFilePath.size());

	foundIndex = fullFilePath.find(standardAssetsFilePath);
	if (foundIndex != std::string::npos) return "?Standard?" + fullFilePath.substr(standardAssetsFilePath.size());

	return fullFilePath;
}

std::string EditorApplication::GetFullFilePath(const std::string& shortFilepath)
{
	size_t foundIndex;

	foundIndex = shortFilepath.find("?Assets?");
	if (foundIndex != std::string::npos) return assetsFilePath + shortFilepath.substr(8);

	foundIndex = shortFilepath.find("Assets");
	if (foundIndex != std::string::npos) return assetsFilePath + shortFilepath.substr(6);

	foundIndex = shortFilepath.find("?Config?");
	if (foundIndex != std::string::npos) return configFilePath + shortFilepath.substr(8);

	foundIndex = shortFilepath.find("Config");
	if (foundIndex != std::string::npos) return configFilePath + shortFilepath.substr(6);

	foundIndex = shortFilepath.find("?Source?");
	if (foundIndex != std::string::npos) return sourceFilePath + shortFilepath.substr(8);

	foundIndex = shortFilepath.find("Source");
	if (foundIndex != std::string::npos) return sourceFilePath + shortFilepath.substr(6);

	foundIndex = shortFilepath.find("?Standard?");
	if (foundIndex != std::string::npos) return assetsFilePath + shortFilepath.substr(11);

	foundIndex = shortFilepath.find("Standard");
	if (foundIndex != std::string::npos) return assetsFilePath + shortFilepath.substr(9);

	return shortFilepath;
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
	modules.push_back(new Console());
}

void EditorApplication::BeginFrame()
{
	EditorProject::BeginFrame();
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

	// To-Do: Make more modular later
	SaveSystem::DisplaySaveSelectedScreen();

	NotificationSystem::RenderNotifications();
}

void EditorApplication::EndFrame()
{
	if (endFrameCallback != nullptr)
	{
		endFrameCallback(GameTime::deltaTime);
	}

	Project::EndFrame();
	EditorWindow::EndFrame();
	EditorProject::EndFrame();
}

void EditorApplication::RenderModules()
{
	for (int i = 0; i < modules.size(); i++)
	{
		if (ImGui::Begin(modules[i]->name.c_str(), modules[i]->GetIsDisplayed(), modules[i]->flags))
		{
			if (ImGui::IsWindowFocused() || ImGui::IsWindowHovered())
			{
				modules[i]->HandleInput();
			}

			modules[i]->Display();
		}
		else
		{

		}
		ImGui::End();
	}
}
