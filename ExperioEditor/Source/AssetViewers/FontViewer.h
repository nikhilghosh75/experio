#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Managers/FontManager.h"

class FontViewer : public EditorModule
{
	void DisplayStats();

	std::string filepath;
public:
	FontRef loadedRef;

	FontViewer();

	virtual void Display() override;
};