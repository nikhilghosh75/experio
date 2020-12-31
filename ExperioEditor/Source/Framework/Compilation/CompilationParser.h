#pragma once
#include <string>
#include <vector>
#include "../../CodeParser/Cpp/CppCompilationError.h"

enum class ECompilationParseStage
{
	CommandListing,
	DeveloperOutput,
	FileListing,
	ErrorOutput,
	Completion
};

class CompilationSystem;

// THIS WILL NOT WORK FOR ANOTHER LANGUAGE
class CompilationParser
{
	static std::vector<std::string> compiledFiles;
	static std::vector<CppCompilationError> compilationErrors;

	static std::string currentString;

	static ECompilationParseStage currentStage;

	static bool isCompiling;

public:
	static void Initialize();

	static void Reset();

	static void StartCompilation();

	static void StopCompilation();

	static bool CompilationSuccessful();

	static void Read(char* buffer);

	friend class CompilationSystem;

private:
	static void ParseCommandOutput();
};