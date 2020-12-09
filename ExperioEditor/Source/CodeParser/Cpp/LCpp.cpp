#include "LCpp.h"
#include "Runtime/Containers/LString.h"

bool LCpp::DoesCppSupport(ECodingLanguageFeature feature)
{
	switch (feature)
	{
	case ECodingLanguageFeature::Async:
	case ECodingLanguageFeature::Classes:
	case ECodingLanguageFeature::Enums:
	case ECodingLanguageFeature::Foreach:
	case ECodingLanguageFeature::Namespaces:
		return true;
	}
	return false;
}

bool LCpp::DoesCppSupport(ECodingLanguageFeature feature, uint16_t version)
{
	switch (feature)
	{
	case ECodingLanguageFeature::Classes:
	case ECodingLanguageFeature::Enums:
	case ECodingLanguageFeature::Namespaces:
		return true;
	case ECodingLanguageFeature::Async: return version >= 11;
	case ECodingLanguageFeature::Coroutines: return version >= 20;
	case ECodingLanguageFeature::Foreach: return version >= 11;
	case ECodingLanguageFeature::Modules: return version >= 23;
	}
	return false;
}

CodeFunction LCpp::ParseCodeFunction(const std::string & str)
{
	CodeFunction func;
	func.accessType = ECodeAccessType::Unknown;

	size_t returnTypeStart = 0;
	if (str.find("static ") != std::string::npos)
	{
		returnTypeStart = str.find("static ") + 7;
		func.keywords = ECodeFunctionKeyword::Static;
	}
	size_t firstSpace = str.find(' ', returnTypeStart);
	func.returnType = str.substr(returnTypeStart, firstSpace - returnTypeStart);

	size_t firstParen = str.find('(');
	func.functionName = str.substr(firstSpace + 1, firstParen - firstSpace - 1);

	size_t firstRightParen = str.find(')');
	if (firstRightParen == firstParen + 1)
	{
		func.arguments = std::vector<CodeArg>();
	}
	else
	{
		std::vector<std::string> argStrings = LString::SeperateStringByChar(
			str.substr(firstParen + 1, firstRightParen - firstParen - 1), ',');
		std::vector<CodeArg> args;
		args.reserve(argStrings.size());
		for (int i = 0; i < argStrings.size(); i++)
		{
			args.push_back(LCodeParser::ParseCodeArg(argStrings[i], ECodingLanguage::CPlusPlus));
		}
		func.arguments = args;
	}

	return func;
}

CodeParam LCpp::ParseCodeParam(const std::string & str)
{
	CodeParam param;

	param.accessType = ECodeAccessType::Unknown;

	size_t returnTypeStart = 0;
	if (str.find("static ") != std::string::npos)
	{
		returnTypeStart = str.find("static ") + 7;
		param.keywords = ECodeParamKeyword::Static;
	}

	// Get variable type
	size_t firstSpace = str.find(' ', returnTypeStart);
	param.type = str.substr(returnTypeStart, firstSpace - returnTypeStart);

	// Get variable name
	size_t firstParen = str.find('(');
	param.name = str.substr(firstSpace + 1, firstParen - firstSpace - 1);

	return param;
}

size_t LCpp::SizeOfDefeaultType(const std::string & name)
{
	if (name == "char") return 1;
	if (name == "unsigned char") return 1;
	if (name == "short") return 2;
	if (name == "unsigned short") return 2;
	if (name == "int") return 4;
	if (name == "unsigned int") return 4;
	if (name == "long long") return 8;
	if (name == "unsigned long long") return 8;
	if (name == "uint8_t") return 1;
	if (name == "int8_t") return 1;
	if (name == "uint16_t") return 2;
	if (name == "int16_t") return 2;
	if (name == "uint32_t") return 4;
	if (name == "int32_t") return 4;
	if (name == "uint64_t") return 8;
	if (name == "int64_t") return 8;
	if (name == "float") return 4;
	if (name == "double") return 8;
	if (name == "bool") return 1;

	return 0;
}
