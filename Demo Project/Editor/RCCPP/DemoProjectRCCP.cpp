#include "RuntimeObjectSystem/RuntimeObjectSystem.h"
#include "RuntimeCompiler/ICompilerLogger.h"
#include "RuntimeObjectSystem/IObject.h"
#include "RuntimeObjectSystem/ObjectInterfacePerModule.h"
#include "DemoProjectEditorMainLoop.h"
#include "DemoProjectSystemTable.h"
#include "DemoProjectLogger.h"
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
	systemTable.runtimeObjectSystem->AddIncludeDir("C:/Users/debgh/source/repos/project-bloo/Experio/Source/Runtime/Debug");
	systemTable.runtimeObjectSystem->AddIncludeDir("C:/Users/debgh/source/repos/project-bloo/Dependencies/RuntimeCompiledCPP");
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