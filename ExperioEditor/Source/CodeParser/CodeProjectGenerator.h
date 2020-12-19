#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include "CodeProject.h"
namespace fs = std::filesystem;

struct FVector2Int;
struct FileBuffer;

class CodeProjectGenerator
{
	std::string rootFilepath;
	fs::recursive_directory_iterator iterator;
	CodeProject* project;
	bool currentlyGenerating = true;

	void ParseFile(std::string filepath);

	bool IsValidFile(std::string filepath) const;
public:
	CodeProjectGenerator();
	CodeProjectGenerator(CodeProject* project);
	CodeProjectGenerator(std::string& rootFilepath, CodeProject* project);

	void GenerateFullProject();
	void StepGenerate();

	bool IsGenerating() const { return currentlyGenerating; }

	void RegenerateProject();

	void RegnerateFullProject();

private:
	std::vector<FVector2Int> GetObjectsInCodeFile(FileBuffer& buffer);

	void ParseObjectsInCodeFile(std::vector<FVector2Int>& objects, FileBuffer& buffer);

	void ParseEnumInCodeFile(FVector2Int location, FileBuffer& buffer);
	void ParseClassInCodeFile(FVector2Int location, FileBuffer& buffer);

	std::string GetNameFromEnd(size_t endOfName, FileBuffer& buffer);
};