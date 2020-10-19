#pragma once
#include <stdint.h>
#include "CodeClass.h"
#include "CodeFunction.h"

enum class ECodingLanguage : uint8_t
{
	None,
	CPlusPlus,
	CSharp,
	Java,
	Python
};

struct FCodeProjectOptions
{
	ECodingLanguage codingLanguage;
	bool generateInstantly;
	// ADD STUFF HERE

	FCodeProjectOptions();

	static FCodeProjectOptions defaultOptions;
};

class CodeProject
{
public:
	ECodingLanguage codingLanguage;
	std::string filepath;

	bool generated = false;

	std::vector<CodeClass> classes;
	std::vector<CodeFunction> functions;

	CodeProject() = delete;
	CodeProject(std::string filepath, FCodeProjectOptions& options = FCodeProjectOptions::defaultOptions);

	void Generate();
};