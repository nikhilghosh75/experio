#pragma once
#include "CodeParam.h"
#include <vector>

enum class ECodeFunctionKeyword : uint8_t
{
	None = 0,
	Const = 1,
	Constexpr = 2,
	ConstexprConst = 3,
};

class CodeFunction
{
	std::string returnType;
	std::string functionName;
	std::vector<std::string> arguments;
	ECodeAccessType accessType;
	ECodeFunctionKeyword keywords;
};