#include "DemoProject.h"

int main(int argc, char** argv)
{
	Project::componentManager = new DemoProjectComponentManager();
	Project::materialManager = new DemoProjectMaterialManager();

	Application app = Application();
	app.Run();
}