#pragma once
#include "InputMap.h"
#include <string>

class InputMapReader
{
public:
	static InputMap ReadInputMap(const std::string& filepath);
};