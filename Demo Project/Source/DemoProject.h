#pragma once
#include "Engine.h"
#include "Runtime/Core/Application.h"
#include "Runtime/Framework/Project.h"

#include "DemoProjectComponentManager.h"
#include "DemoProjectMaterialManager.h"
#include <Windows.h>

extern "C" __declspec(dllexport) void SetupProject();
extern "C" __declspec(dllexport) void RunProject();