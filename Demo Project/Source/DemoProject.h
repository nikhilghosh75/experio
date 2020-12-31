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
