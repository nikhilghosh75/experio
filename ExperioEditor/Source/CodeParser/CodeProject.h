#pragma once
#include <stdint.h>
#include "CodeClass.h"
#include "CodeFunction.h"
#include "CodeEnum.h"

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
	std::vector<CodeEnum> enums;
	std::vector<CodeFunction> functions;

	CodeProject() = delete;
	CodeProject(std::string filepath, FCodeProjectOptions& options = FCodeProjectOptions::defaultOptions);

	void Generate();

	void PushClass(const CodeClass& codeClass);
	void PushEnum(const CodeEnum& codeEnum);
	void PushFunction(const CodeFunction& function);

	void Empty();
		
	CodeClass& EmplaceClass();
	CodeClass& EmplaceClass(const std::string& name);

	CodeEnum& EmplaceEnum();
	CodeEnum& EmplaceEnum(const std::string& name);
	CodeEnum& EmplaceEnum(const std::string& name, EEnumDataType dataType);

	CodeFunction& EmplaceFunction();
	CodeFunction& EmplaceFunction(const std::string& returnType, const std::string& functionName);
};