#include "DemoProject.h"
#include "Runtime/Framework/BinaryParams.h"
#include "Runtime/Framework/SceneLoader.h"
#include "Runtime/Core/Window.h"
#include "ThirdParty/Nameof/nameof.hpp"

std::string projectName = "Test Project";

template <class T>
unsigned int DefaultClassTypeToInt()
{
	return 0;
}

template<> unsigned int DefaultClassTypeToInt<TestComponent>() { return 2; }
template<> unsigned int DefaultClassTypeToInt<VirtualCamera>() { return 100; }
template<> unsigned int DefaultClassTypeToInt<MeshComponent>() { return 101; }
template<> unsigned int DefaultClassTypeToInt<ParticleSystem>() { return 102; }
template<> unsigned int DefaultClassTypeToInt<Billboard>() { return 103; }
template<> unsigned int DefaultClassTypeToInt<TextComponent>() { return 104; }

template <class T>
std::string DefaultClassTypeToString()
{
	return NAMEOF_TYPE(T);
}

// Game Functions Here
extern "C" __declspec(dllexport) void SetupProject()
{
	Project::componentManager = new DemoProjectComponentManager();
	Project::materialManager = new DemoProjectMaterialManager();
	printf("Setup Project");
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

/*
extern "C" __declspec(dllexport) bool LoadScene(std::string filename, int sceneSlot)
{
	bool returnValue = SceneLoader::LoadSceneFromFile(filename, sceneSlot, ESceneProjectCompareType::None);
	Scene::Activate(sceneSlot);
	return returnValue;
}

extern "C" __declspec(dllexport) void SetupGraphics(HWND hwnd)
{
	HDC deviceContext = GetDC(hwnd);
	HGLRC glRenderContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, glRenderContext);

	glewInit();
}

extern "C" __declspec(dllexport) void SetWindowSize(int width, int height)
{
	// printf("Set Window Size\n");
	Window::ResizeWindow(EWindowResizeType::EditorResize, width, height);
}
*/

#ifdef PLATFORM_WINDOWS
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif