#pragma once
#include "CodeParam.h"

class CodeMember
{
public:
	std::string type;
	std::string name;
	ECodeAccessType accessType;
	bool isStatic;
};