#pragma once
#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Managers/TextureManager.h"

class ImageViewer : public EditorModule
{
	void DisplayStats();

	std::string filepath;
public:
	TextureRef loadedRef;

	ImageViewer();

	virtual void Display() override;
};