#pragma once
#include "../Core/EditorModule.h"
#include "Runtime/Input/InputMap.h"

class InputMapViewer : public EditorModule
{
	bool loaded;
	std::string mapName;
	std::string filepath;
	InputMap currentMap;

public:
	InputMapViewer();

	virtual void Display() override;

	void Load(const std::string& filepath);

private:
	void DisplayEmpty();

	void DisplayInputMap();
};