#include "Core/EditorApplication.h"
#include "DemoProject.h"

void SetupProjectEditor()
{
	Project::componentManager = new DemoProjectComponentManager();
	Project::materialManager = new DemoProjectMaterialManager();
}

int main(int argc, char** argv)
{
	SetupProjectEditor();
	EditorApplication application;
	application.Run();
	delete Project::componentManager;
}