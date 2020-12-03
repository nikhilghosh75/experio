#include "RuntimeObjectSystem/RuntimeObjectSystem.h"
#include "RuntimeObjectSystem/RuntimeLinkLibrary.h"
#include "RuntimeCompiler/ICompilerLogger.h"
#include "RuntimeObjectSystem/IObject.h"
#include "RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "DemoProjectEditorMainLoop.h"
#include "DemoProjectSystemTable.h"
#include "DemoProjectLogger.h"
#include "Core/EditorApplication.h"
#include "Runtime/Time/GameTime.h"
#include "Runtime/Framework/Project.h"
#include "imgui.h"
#include <stdarg.h>

static DemoProjectLogger logger; // Figure out logger
static SystemTable systemTable;

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

	systemTable.runtimeObjectSystem->SetAdditionalCompileOptions("-std=c++17");
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
}