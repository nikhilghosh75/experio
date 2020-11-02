#include "DemoProject.h"
#include "Runtime/Framework/SceneLoader.h"
#include "Runtime/Core/Window.h"
#include "ThirdParty/Nameof/nameof.hpp"

std::string projectName = "Test Project";

unsigned short DefaultTagStringToNum(const char* string)
{
	if (strcmp(string, "Player"))
	{
		return 1;
	}
	if (strcmp(string, "Enemy"))
	{
		return 2;
	}
	return 0;
}

std::string DefaultTagNumToString(unsigned short num)
{
	switch (num)
	{
	case 1:
		return "Player";
	case 2:
		return "Enemy";
	}
	return "";
}

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

std::vector<std::string> GetParamsList(unsigned int classId)
{
	switch (classId)
	{
	case 2:
		return std::vector<std::string>();
	case 100:
		return std::vector<std::string>({ "priority", "fieldOfView", "nearClipPlane", "farClipPlane" });
	case 101:
		return std::vector<std::string>({ "meshShader", "meshData", "isVisible" });
	case 102:
		return std::vector<std::string>();
	case 103:
		return std::vector<std::string>({ "billboardTexture", "sizeType", "orientation", "billboardSize" });
	case 104:
		return std::vector<std::string>({ "margins", "fontSize", "text", "font", "shader" });
	}
	return std::vector<std::string>();
}

template<class T>
void SetComponentParams(std::vector<std::string> params, T* component) { }

template<> void SetComponentParams(std::vector<std::string> params, MeshComponent* component)
{
	component->material = (MeshMaterial*)ParseMaterial(params[0]);
	component->meshData = ParseMesh(params[1]);
	component->isVisible = ParseBool(params[2]);
}

template<> void SetComponentParams(std::vector<std::string> params, Billboard* component)
{
	component->billboardTexture = ParseTexture(params[0]);
	component->sizeType = (EBillboardSizeType)ParseInt(params[1]);
	component->orientation = (EBilboardOrientation)ParseInt(params[2]);
	component->billboardSize = ParseVector2(params[3]);
}

template<> void SetComponentParams(std::vector<std::string> params, TextComponent* component)
{
	component->margins = ParseFloat(params[0]);
	component->fontSize = ParseInt(params[1]);
	component->text = params[2];
	component->font = ParseFont(params[3]);
	component->shader = ParseShader(params[4]);
}

void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId)
{
	switch (classId)
	{
	case 2: {PB_EMPLACE_COMPONENT(TestComponent, classId); PB_START_COMPONENT(); } break;
	case 100: { CameraSystem::AddComponent(params, gameObject); } break;
	case 101: { PB_EMPLACE_COMPONENT(MeshComponent, classId); PB_START_COMPONENT(); } break;
	case 102: { PB_EMPLACE_COMPONENT(ParticleSystem, classId); PB_START_COMPONENT(); } break;
	case 103: { PB_EMPLACE_COMPONENT(Billboard, classId); PB_START_COMPONENT(); } break;
	case 104: { PB_EMPLACE_COMPONENT(TextComponent, classId); PB_START_COMPONENT(); } break;
	}
}

size_t SizeOfComponent(unsigned int classId)
{
	switch (classId)
	{
	case 2: return sizeof(TestComponent);
	case 100: return sizeof(VirtualCamera);
	case 101: return sizeof(MeshComponent);
	case 102: return sizeof(ParticleSystem);
	case 103: return sizeof(Billboard);
	case 104: return sizeof(TextComponent);
	}
	return 0;
}

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
	Application app = Application();
	app.Run();
}

extern "C" __declspec(dllexport) void Update()
{
	printf("%i %i\n", Window::GetWindowData().width, Window::GetWindowData().height);
	glClearColor(0, 0, 1, 1);
	Renderer renderer;
	renderer.LogRenderingError();
	renderer.TempModelRenderer();
	//Project::componentManager->Update();
	Project::EndFrame();
	renderer.LogRenderingError();
}

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