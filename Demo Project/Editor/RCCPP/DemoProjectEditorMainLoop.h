#pragma once

#include "RuntimeObjectSystem\RuntimeLinkLibrary.h"
RUNTIME_COMPILER_LINKLIBRARY("C:/Users/debgh/source/repos/project-bloo/bin/x64/Debug/Engine/Engine.lib");

struct IRCCppMainLoop
{
	virtual void MainLoop() = 0;
};