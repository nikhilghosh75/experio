#include "GameTime.h"
#include "../Input/Input.h"
#include "../Framework/Project.h"

float GameTime::deltaTime = 0.f;
float GameTime::fixedDeltaTime = 0.02f;
unsigned int GameTime::frameCount = 0;
FDateTime GameTime::lastTime;
float GameTime::timeSinceStart = 0.f;

void GameTime::StartGame()
{
	timeSinceStart = 0.f;
	frameCount = 0;
	lastTime = FDateTime::NowHighRes();

	Input::Init();
}

void GameTime::OnBeginFrame()
{
	if(Project::inEditor) Input::OnImguiUpdate();
}

void GameTime::OnEndFrame()
{
	FDateTime currentTime = FDateTime::NowHighRes();
	deltaTime = (float)((currentTime.ticks - lastTime.ticks) / TICKSPERSECOND);
	lastTime = currentTime;

	frameCount++;
	timeSinceStart += deltaTime;

	Input::OnFrameEnd();
}
