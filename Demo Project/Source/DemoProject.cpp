#include "DemoProject.h"
#include "Runtime/Core/Window.h"
#include "Runtime/Framework/BinaryParams.h"
#include "Runtime/Framework/Params.h"
#include "ThirdParty/Nameof/nameof.hpp"

std::string projectName = "Demo Project";

template <class T> unsigned int DefaultClassTypeToInt() { return 0; }

template<> unsigned int DefaultClassTypeToInt<TextComponent>() { return 104; }
template<> unsigned int DefaultClassTypeToInt<Spaceship>() { return 1024; }
template<> unsigned int DefaultClassTypeToInt<VirtualCamera>() { return 100; }
template<> unsigned int DefaultClassTypeToInt<MeshComponent>() { return 101; }
template<> unsigned int DefaultClassTypeToInt<ParticleSystem>() { return 102; }
template<> unsigned int DefaultClassTypeToInt<Billboard>() { return 103; }

template <class T> std::string DefaultClassTypeToString() { return NAMEOF_TYPE(T); }

extern "C" __declspec(dllexport) void SetupProject()
{
	Project::componentManager = new DemoProjectComponentManager();
	Project::materialManager = new DemoProjectMaterialManager();
}
extern "C" __declspec(dllexport) void RunProject()
{
	Application app;
	app.Run();
}
extern "C" __declspec(dllexport) ComponentManager* CreateComponentManager()
{
	return new DemoProjectComponentManager();
}
extern "C" __declspec(dllexport) MaterialManager* CreateMaterialManager()
{
	return new DemoProjectMaterialManager();
}
