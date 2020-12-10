#pragma once
#include "CodeParam.h"
#include "CodeArg.h"
#include <vector>

enum class ECodeFunctionKeyword : uint8_t
{
	None = 0,
	Const = 1,
	Constexpr = 2,
	ConstexprConst = 3,
	Static = 4,
	StaticConst = 5,
	StaticConstexpr = 6,
	StaticConstexprConst = 7,
	Virtual = 8,
	VirtualConst = 9
};

class CodeFunction
{
public:
	std::string returnType;
	std::string functionName;
	std::vector<CodeArg> arguments;
	ECodeAccessType accessType;
	ECodeFunctionKeyword keywords;

	CodeFunction() = default;

	CodeFunction(const std::string& returnType, const std::string& functionName)
	{
		this->returnType = returnType;
		this->functionName = functionName;
		this->accessType = ECodeAccessType::Unknown;
		this->keywords = ECodeFunctionKeyword::None;
	}
};