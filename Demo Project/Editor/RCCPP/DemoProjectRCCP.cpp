#include "ThirdParty\RCCPP.h"
#include "DemoProjectEditorMainLoop.h"
#include "DemoProjectSystemTable.h"
#include "DemoProjectLogger.h"
#include "Core/EditorApplication.h"
#include "Framework/CompilationInfo.h"
#include "Framework/EditorProject.h"
#include "Framework/SceneSaver.h"
#include "Runtime/Time/GameTime.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Framework/SceneLoader.h"
#include "imgui.h"
#include <stdarg.h>

static DemoProjectLogger logger; // Figure out logger
static SystemTable systemTable;

static BuildTool projectBuildTool;

bool isBuilding = false;

typedef ComponentManager* (__cdecl *GETCOMPONENTMANAGERPROC)();
typedef MaterialManager* (__cdecl *GETMATERIALMANAGERPROC)();

bool IsCompileComplete();
void LoadCompiledProject();

bool RCCppInit()
{
	// PerModuleInterface::g_pSystemTable = &systemTable;
	systemTable.ImContext = ImGui::GetCurrentContext();
	systemTable.runtimeObjectSystem = new RuntimeObjectSystem();
	if (!systemTable.runtimeObjectSystem->Initialise(&logger, &systemTable))
	{
		delete systemTable.runtimeObjectSystem;
		return false;
	}
	
	systemTable.runtimeObjectSystem->CleanObjectFiles();

	systemTable.runtimeObjectSystem->AddIncludeDir((EditorApplication::experioFilePath + "/Source").c_str());
	systemTable.runtimeObjectSystem->AddIncludeDir((EditorApplication::experioEditorFilePath + "/Source").c_str());
	systemTable.runtimeObjectSystem->AddIncludeDir((EditorApplication::experioDependenciesFilePath + "/RuntimeCompiledCPP").c_str());
	systemTable.runtimeObjectSystem->AddIncludeDir((EditorApplication::experioDependenciesFilePath + "/glm").c_str());
	systemTable.runtimeObjectSystem->AddIncludeDir((EditorApplication::experioDependenciesFilePath + "/GLEW/include").c_str());
	systemTable.runtimeObjectSystem->AddIncludeDir((EditorApplication::experioDependenciesFilePath + "/imgui").c_str());

	systemTable.runtimeObjectSystem->AddLibraryDir((EditorApplication::experioBinariesFilePath + "/x64/Debug/Engine").c_str());

	systemTable.runtimeObjectSystem->SetAdditionalCompileOptions("/std:c++17");

	projectBuildTool.Initialise(&logger);
	return true;
}

void RCCppCleanup()
{
	delete systemTable.runtimeObjectSystem;
}

void RCCMainLoop()
{
	systemTable.mainLoop->MainLoop();
}

void RCCUpdate()
{
	if (systemTable.runtimeObjectSystem->GetIsCompiledComplete())
	{
		systemTable.runtimeObjectSystem->LoadCompiledModule();
	}

	if (!systemTable.runtimeObjectSystem->GetIsCompiling())
	{
		float deltaTime = 1.0f / ImGui::GetIO().Framerate;
		systemTable.runtimeObjectSystem->GetFileChangeNotifier()->Update(deltaTime);
	}

	if (IsCompileComplete())
	{
		LoadCompiledProject();
	}
}

namespace DemoProject::RCCPP
{
	// Extend later if multiple dlls will be created
	std::vector<BuildTool::FileToBuild> GetFilesToBuild()
	{
		std::vector<std::string>& gameCompilePaths = EditorProject::gameCompileFiles;

		std::vector<BuildTool::FileToBuild> filesToBuild;
		filesToBuild.reserve(gameCompilePaths.size());

		for (size_t i = 0; i < gameCompilePaths.size(); i++)
		{
			filesToBuild.emplace_back(FileSystemUtils::Path(gameCompilePaths[i].c_str()), true);
		}
		return filesToBuild;
	}

	std::vector<FileSystemUtils::Path> GetLinkedLibraries()
	{
		// $(SolutionDir)Dependencies\GLEW\lib\Release\x64;$(SolutionDir)bin\x64\Release\Engine;
		// glew32s.lib;opengl32.lib
		std::vector<FileSystemUtils::Path> linkedLibraries;

		linkedLibraries.push_back(EditorApplication::experioBinariesFilePath + "/x64/Debug/Engine/Engine.lib");
		linkedLibraries.push_back(EditorApplication::experioDependenciesFilePath + "/GLEW/lib/Release/x64/glew32s.lib");
		linkedLibraries.push_back("opengl32.lib");

		return linkedLibraries;
	}

	CompilerOptions GetCompilerOptions()
	{
		CompilerOptions options;

		options.includeDirList.emplace_back((EditorApplication::experioFilePath + "/Source").c_str());
		options.includeDirList.emplace_back((EditorApplication::experioEditorFilePath + "/Source").c_str());
		options.includeDirList.emplace_back((EditorApplication::experioDependenciesFilePath + "/RuntimeCompiledCPP").c_str());
		options.includeDirList.emplace_back((EditorApplication::experioDependenciesFilePath + "/glm").c_str());
		options.includeDirList.emplace_back((EditorApplication::experioDependenciesFilePath + "/GLEW/include").c_str());
		options.includeDirList.emplace_back((EditorApplication::experioDependenciesFilePath + "/imgui").c_str());

		options.libraryDirList.emplace_back((EditorApplication::experioBinariesFilePath + "/x64/Debug/Engine").c_str());

		options.compileOptions = "/std:c++17";
		options.linkOptions = "";

		options.baseIntermediatePath = EditorApplication::binariesFilePath + "/Intermediate";
		options.intermediatePath = EditorApplication::binariesFilePath + "/Intermediate/Temp";

		options.optimizationLevel = RCppOptimizationLevel::RCCPPOPTIMIZATIONLEVEL_DEBUG;

		options.preproccessorMacros.push_back("PLATFORM_WINDOWS");

		return options;
	}
}

void RCCCompileProject()
{
	FileSystemUtils::Path dllBuildPath = EditorApplication::binariesFilePath + "/Intermediate/Temp.dll";
	// FileSystemUtils::Path dllBuildPath = "'C:/Users/debgh/source/repos/project-bloo/Demo Project/Binaries/Intermediate/Temp.dll'";

	std::vector<BuildTool::FileToBuild> filesToBuild = DemoProject::RCCPP::GetFilesToBuild();
	std::vector<FileSystemUtils::Path> linkedLibraries = DemoProject::RCCPP::GetLinkedLibraries();

	// Add required source files if necessary

	CompilerOptions compilerOptions = DemoProject::RCCPP::GetCompilerOptions();

	projectBuildTool.BuildModule(filesToBuild, compilerOptions, linkedLibraries, dllBuildPath);

	isBuilding = true;
}

bool IsCompileComplete()
{
	return isBuilding && projectBuildTool.GetIsComplete();
}

void LoadCompiledProject()
{
	std::string dllBuildPath = EditorApplication::binariesFilePath + "/Intermediate/Temp.dll";
	HINSTANCE hinstLib = LoadLibraryA(TEXT(dllBuildPath.c_str()));

	GETCOMPONENTMANAGERPROC componentManagerProc = (GETCOMPONENTMANAGERPROC)GetProcAddress(hinstLib, "CreateComponentManager");
	if (componentManagerProc != NULL)
	{
		SceneSaver::SaveScene(0, "tempScene.pbscene");
		Scene::UnloadAllScenes();

		ComponentManager* newManager = componentManagerProc();
		delete Project::componentManager;
		Project::componentManager = newManager;
		
		SceneLoader::LoadSceneFromFile("tempScene.pbscene");
	}

	GETMATERIALMANAGERPROC materialManagerProc = (GETMATERIALMANAGERPROC)GetProcAddress(hinstLib, "CreateMaterialManager");
	if (materialManagerProc != NULL)
	{
		// Add stuff here
	}

	isBuilding = false;
}

FCompilationInfo GetCompilationInfo()
{
	// return FCompilationInfo(systemTable.runtimeObjectSystem->GetIsCompiling(), 0.0f);
	return FCompilationInfo(isBuilding && !projectBuildTool.GetIsComplete(), 0.0f);
}