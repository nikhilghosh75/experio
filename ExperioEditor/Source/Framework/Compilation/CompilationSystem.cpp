#include "CompilationSystem.h"
#include "CompilationParser.h"

std::function<void(FCompilationResult)> CompilationSystem::finishCompilationCallback;

void CompilationSystem::StartCompilation()
{
	CompilationParser::StartCompilation();
}

void CompilationSystem::FinishCompilation()
{
	CompilationParser::StopCompilation();

	FCompilationResult result(CompilationParser::compilationErrors, 
		CompilationParser::CompilationSuccessful());
	if (finishCompilationCallback)
	{
		finishCompilationCallback(result);
	}
}
