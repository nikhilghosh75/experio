#include "Core/EditorApplication.h"
#include "DemoProject.h"

bool RCCppInit();
void RCCppCleanup();
void RCCMainLoop();
void RCCUpdate();

void SetupProjectEditor()
{
	Project::componentManager = new DemoProjectComponentManager();
	Project::materialManager = new DemoProjectMaterialManager();

	Project::projectName = "Demo Project";
}

void ShutdownProjectEditor()
{
	delete Project::componentManager;
	delete Project::materialManager;
}

void OnBeginFrame(float deltaTime)
{
	RCCMainLoop();
}

void OnEndFrame(float deltaTime)
{
	RCCUpdate();
}

int main(int argc, char** argv)
{
	SetupProjectEditor();
	EditorApplication application;
	application.Setup();
	RCCppInit();

	application.SetBeginFrameCallback(OnBeginFrame);
	application.SetEndFrameCallback(OnEndFrame);

	application.Run();

	application.Shutdown();
	ShutdownProjectEditor();
	RCCppCleanup();
}