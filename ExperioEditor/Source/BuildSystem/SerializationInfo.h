#pragma once
#include "Runtime/Framework/Params.h"

struct FSerializationInfo
{
	EParamType type;
	std::string typeName;
	std::string name;
	size_t offset;
};