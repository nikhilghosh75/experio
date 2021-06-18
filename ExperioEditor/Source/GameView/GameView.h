#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Rendering/FrameBuffer.h"
#include "Runtime/Rendering/Renderer.h"

class GameView : public EditorModule
{
	Renderer renderer;

	TextureRef playButtonImage;
	TextureRef pauseButtonImage;
	TextureRef stopButtonImage;

	Framebuffer framebuffer;

	ImVec2 lastSize;

	bool locked;

	void CreateMenu();
public:
	static GameView* gameView;

	GameView();

	virtual void Display() override;

	void Lock();

	void Unlock();
};