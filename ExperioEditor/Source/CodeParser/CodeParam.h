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

	CodeParam() = default;

	CodeParam(const std::string& type, const std::string& name)
	{
		this->type = type;
		this->name = name;
		this->accessType = ECodeAccessType::Private;
		this->keywords = ECodeParamKeyword::None;
	}

	CodeParam(const std::string& type, const std::string& name, ECodeAccessType accessType)
	{
		this->type = type;
		this->name = name;
		this->accessType = accessType;
		this->keywords = ECodeParamKeyword::None;
	}

	CodeParam(const std::string& type, const std::string& name, ECodeAccessType accessType, ECodeParamKeyword keyword)
	{
		this->type = type;
		this->name = name;
		this->accessType = accessType;
		this->keywords = keyword;
	}

	static bool IsStatic(ECodeParamKeyword keyword)
	{
		return keyword == ECodeParamKeyword::Static || keyword == ECodeParamKeyword::StaticConst;
	}
};