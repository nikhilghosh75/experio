#include "Application.h"
#include "Window.h"
#include <iostream>
#include "../Rendering/Renderer.h"
#include "../Framework/AssetMap.h"
#include "../Framework/Framework.h"
#include "../Framework/Project.h"
#include "../Framework/Scene.h"
#include "../Time/GameTime.h"
#include "../Framework/SceneLoader.h"
#include "../Rendering/Managers/TextureManager.h"

Application::Application()
{
}


Application::~Application()
{
}

void Application::Run()
{
	Window newWindow;
	newWindow.InstantiateWindow();

	Renderer tempRenderer;
	tempRenderer.MakeCurrent();

	AssetMap::ReadAssetMap("map.pbasmap");
	SceneLoader::LoadSceneFromFile(AssetMap::defaultScenePath, 0);
	Scene::Activate(0);

	GameTime::StartGame();

	while (newWindow.isActive)
	{
		newWindow.OnUpdate();
		tempRenderer.OnNewFrame();
		if (!newWindow.isActive)
		{
			break;
		}
		tempRenderer.Clear();
		Project::componentManager->Update();
		tempRenderer.OnEndFrame();
		GameTime::OnEndFrame();
		// Debug::log << "DeltaTime = " << GameTime::deltaTime << Debug::endl;
	}

	Debug::FlushToFile();
	std::cin.get();
}