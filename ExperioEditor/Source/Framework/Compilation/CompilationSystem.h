#pragma once

#include "CompilationInfo.h"
#include "CompilationResult.h"
#include <functional>

class CompilationSystem
{
public:
	static std::function<void(FCompilationResult&)> finishCompilationCallback;

	static void StartCompilation();

	static void FinishCompilation();
};