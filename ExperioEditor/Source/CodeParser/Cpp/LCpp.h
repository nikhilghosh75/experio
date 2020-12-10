#pragma once
#include "../LCodeParser.h"

class LCpp
{
public:
	static bool DoesCppSupport(ECodingLanguageFeature feature);

	static bool DoesCppSupport(ECodingLanguageFeature feature, uint16_t version);

	static CodeFunction ParseCodeFunction(const std::string& str);

	static CodeParam ParseCodeParam(const std::string& str);

	static size_t SizeOfDefeaultType(const std::string& name);
};