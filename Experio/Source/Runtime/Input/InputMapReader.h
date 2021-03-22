#pragma once
#include "InputMap.h"
#include <string>
#include <fstream>

class InputMapReader
{
public:
	static InputMap ReadInputMap(const std::string& filepath);

private:
	static EInputType StringToInputType(const std::string& type);

	static InputCode StringToInputCode(const std::string& str, EInputType inputType);

	static void ParseAction(std::ifstream& inFile, InputConfig& config);

	static void ParseAxis(std::ifstream& inFile, InputConfig& config);
};