#pragma once
#include <string>

enum class ECodeAccessType : uint8_t
{
	Public,
	Private,
	Protected,
	Unknown
};

enum class ECodeParamKeyword : uint8_t
{
	None = 0,
	Const = 1,
	Static = 2,
	StaticConst = 3,
};

class CodeParam
{
public:
	std::string type;
	std::string name;
	ECodeAccessType accessType;
	ECodeParamKeyword keywords;
};