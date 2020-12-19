#pragma once
#include <string>

struct CodeArg
{
	std::string type;
	std::string name;
	bool isConst;

	CodeArg() = default;
	
	CodeArg(const std::string& type, const std::string& name, bool isConst)
	{
		this->type = type;
		this->name = name;
		this->isConst = isConst;
	}
};