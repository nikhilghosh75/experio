#pragma once
#include "FDateTime.h"
#include "../Core/Application.h"
#include "../Framework/Project.h"

const float TICKSPERSECOND = 10000000.f;

class GameTime
{
	friend class Application;
	friend class Project;

	static FDateTime lastTime;

	static void StartGame();

	static void OnEndFrame();

public:
	static float deltaTime;

	static float fixedDeltaTime;

	static unsigned int frameCount;

	static float timeSinceStart;
};