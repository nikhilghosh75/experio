#pragma once

#include "RuntimeObjectSystem/RuntimeInclude.h"
#include "RuntimeObjectSystem/ObjectInterfacePerModule.h"

RUNTIME_MODIFIABLE_INCLUDE;

struct IRCCppMainLoop;
struct ImGuiContext;
struct IRuntimeObjectSystem;

static SystemTable*& g_pSys = PerModuleInterface::g_pSystemTable;

struct SystemTable
{
	IRCCppMainLoop* mainLoop = nullptr;
	ImGuiContext* ImContext = nullptr;
	IRuntimeObjectSystem* runtimeObjectSystem = nullptr;
};