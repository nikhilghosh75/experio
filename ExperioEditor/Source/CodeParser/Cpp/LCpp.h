#pragma once
#include "../LCodeParser.h"

class LCpp
{
public:
	static size_t AlignForward(size_t offset, size_t size);

	static bool DoesCppSupport(ECodingLanguageFeature feature);

	static bool DoesCppSupport(ECodingLanguageFeature feature, uint16_t version);

	static bool IsIntegerType(const std::string& typeName);

	static CodeFunction ParseCodeFunction(const std::string& str);

	static CodeParam ParseCodeParam(const std::string& str);

	static size_t SizeOfDefeaultType(const std::string& name);
};