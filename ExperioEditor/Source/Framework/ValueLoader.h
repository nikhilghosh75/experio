#pragma once
#include <string>
#include "Values.h"

class ValueLoader
{
public:
	static void LoadValues(std::string fileName);

private:
	static EValueType GetTypeFromString(const char* type);
};