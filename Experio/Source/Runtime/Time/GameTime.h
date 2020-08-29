#pragma once
#include "FDateTime.h"
#include "../Core/GApplication.h"

const float TICKSPERSECOND = 10000000.f;

class GameTime
{
	friend class GApplication;

	static FDateTime lastTime;

	static void StartGame();

	static void OnEndFrame();

public:
	static float deltaTime;

	static float fixedDeltaTime;

	static unsigned int frameCount;

	static float timeSinceStart;
};