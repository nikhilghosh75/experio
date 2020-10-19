#pragma once
#include <string>

enum class ECodeAccessType : uint8_t
{
	Public,
	Private,
	Protected
};

class CodeParam
{
public:
	std::string type;
	std::string name;
	ECodeAccessType accessType;
};