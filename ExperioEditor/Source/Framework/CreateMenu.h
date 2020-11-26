#pragma once

#include <string>

class CreateMenu
{
	static bool cppCreateMenu;
	static bool materialCreateMenu;

public:
	static void DisplayCreateMenu();

	static void CreateDatatable(const std::string& filepath);

	static void CreateScene(const std::string& filepath);

	static void DisplayCPPCreateMenu();

	static void DisplayMaterialCreateMenu();
};