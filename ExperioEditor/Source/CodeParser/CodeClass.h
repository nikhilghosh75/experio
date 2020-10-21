#pragma once
#include "CodeParam.h"
#include "CodeFunction.h"
#include <vector>

class CodeClass
{
public:
	std::vector<CodeParam> params;
	std::vector<CodeFunction> functions;
	std::string name;
	std::string filename;
	std::vector<CodeClass*> inheritance;
};