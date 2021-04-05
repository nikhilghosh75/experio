#pragma once
#include "../LCodeParser.h"

class LCpp
{
public:
	static size_t AlignForward(size_t offset, size_t size, bool isDefault = true);

	static bool DoesCppSupport(ECodingLanguageFeature feature);

	static bool DoesCppSupport(ECodingLanguageFeature feature, uint16_t version);

	static bool IsIntegerType(const std::string& typeName);

	static bool IsPointer(const std::string& typeName);

	static CodeFunction ParseCodeFunction(const std::string& str);

	static CodeParam ParseCodeParam(const std::string& str);

	static size_t SizeOfDefaultType(const std::string& name);

	static size_t SizeOfStringType(const std::string& name);
};