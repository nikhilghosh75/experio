#include "PlaySystem.h"
#include "SceneSaver.h"
#include "Runtime/Framework/Project.h"
#include "Runtime/Framework/Scene.h"
#include "Runtime/Framework/SceneLoader.h"

EPlaySystemState PlaySystem::playSystemState = EPlaySystemState::NotPlaying;

void PlaySystem::StartGame()
{
	if (playSystemState != EPlaySystemState::NotPlaying) return;

	playSystemState = EPlaySystemState::Playing;

	// Save Scene
	SceneSaver::SaveScene(0, "tempScene.pbscene");

	Project::componentManager->Start();
}

void PlaySystem::PauseGame()
{
	if (playSystemState != EPlaySystemState::Playing) return;

	playSystemState = EPlaySystemState::Paused;
}

void PlaySystem::UnpauseGame()
{
	if (playSystemState != EPlaySystemState::Paused) return;

	playSystemState = EPlaySystemState::Playing;
}

void PlaySystem::StopGame()
{
	if (playSystemState == EPlaySystemState::NotPlaying) return;

	playSystemState = EPlaySystemState::NotPlaying;

	Scene::UnloadAllScenes();
	SceneLoader::LoadSceneFromFile("tempScene.pbscene", 0);
}
