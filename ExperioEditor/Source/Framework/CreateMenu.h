#pragma once

#include <string>

enum class ECodeClassBase
{
	None,
	Component,
	System,
	Library
};

class CreateMenu
{
	static bool cppCreateMenu;
	static bool materialCreateMenu;

	static ECodeClassBase currentClassType;

public:
	static void Initialize();

	static void DisplayCreateMenu();

	static void DisplayCPPCreateMenu();

	static void DisplayMaterialCreateMenu();

private:
	static void DisplayClassType(const std::string& name, const std::string& tooltipName, ECodeClassBase classBase);

	static std::string CodeClassBaseToString(ECodeClassBase base);
};