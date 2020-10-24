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
};

class CodeFunction
{
public:
	std::string returnType;
	std::string functionName;
	std::vector<CodeArg> arguments;
	ECodeAccessType accessType;
	ECodeFunctionKeyword keywords;
};