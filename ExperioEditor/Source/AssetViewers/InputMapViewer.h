#pragma once
#include "../Core/EditorModule.h"
#include "Runtime/Input/InputMap.h"
#include <fstream>

class InputMapViewer : public EditorModule
{
	bool loaded;
	std::string mapName;
	std::string filepath;
	InputMap currentMap;

	int categoryIndex;
	int configIndex;
	bool action; // Is an action selected or is an axis selected
	int actionIndex;

public:
	InputMapViewer();

	virtual void Display() override;

	void Load(const std::string& filepath);

private:
	void DisplayEmpty();

	void DisplayInputMap();

	void DisplayCategories();

	void DisplayCategoryInfo();

	void DisplayConfigs();

	void DisplayConfigInfo();

	void DisplayActionsAndAxes();

	void DisplayActions();

	void DisplayAxes();

	void DisplayActionAndAxis();

	void DisplayAction();

	void DisplayAxis();

	void DisplayInputCode(EInputType inputType, InputCode& code);

	// Savers

	void SaveInputMap();

	void SaveCategory(std::ofstream& outFile, InputCategory& category);

	void SaveConfig(std::ofstream& outFile, InputConfig& config);
};