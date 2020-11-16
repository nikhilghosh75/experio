#pragma once
#include "Values.h"

class ValueSaver
{
public:
	static void SaveValues();

	static void SaveValue(EValueType type);

private:
	static std::string TypeToFileName(EValueType type);

	static std::string TypeToName(EValueType type);
};