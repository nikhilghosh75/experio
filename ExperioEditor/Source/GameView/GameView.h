#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/Renderer.h"

class GameView : public EditorModule
{
	Renderer renderer;

	TextureRef playButtonImage;
	TextureRef pauseButtonImage;
	TextureRef stopButtonImage;

	void CreateMenu();
public:
	GameView();

	virtual void Display() override;
};