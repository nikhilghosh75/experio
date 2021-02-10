#include "Core/HubApplication.h"

int main(int argc, char** argv)
{
	HubApplication application;
	application.Setup();
	application.Run();
	application.Shutdown();
}