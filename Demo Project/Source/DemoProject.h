#pragma once
#include "Runtime/Core/Application.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Rendering/Renderer.h"
#include "Runtime/Time/GameTime.h"

#include "DemoProjectComponentManager.h"
#include "DemoProjectMaterialManager.h"
#include <Windows.h>

extern "C" __declspec(dllexport) void SetupProject();
extern "C" __declspec(dllexport) void RunProject();
extern "C" __declspec(dllexport) void Update();
extern "C" __declspec(dllexport) ComponentManager* CreateComponentManager();
extern "C" __declspec(dllexport) MaterialManager* CreateMaterialManager();
/*
extern "C" __declspec(dllexport) bool LoadScene(std::string filename, int sceneSlot);
extern "C" __declspec(dllexport) void SetupGraphics(HWND hwnd);
extern "C" __declspec(dllexport) void SetWindowSize(int width, int height);
*/