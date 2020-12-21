#pragma once
#include <string>
#include "Runtime/Framework/Params.h"

class LSerializationOperations
{
public:
	static std::string BinaryParseFunctionFromType(EParamType type);

	static std::string BinarySaveFunctionFromType(EParamType type);

	static std::string ParseFunctionFromType(EParamType type);

	static std::string SaveFunctionFromType(EParamType type);
};