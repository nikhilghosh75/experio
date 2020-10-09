#include "Application.h"
#include "Window.h"
#include <iostream>
#include "../Debug/TempProfiler.h"
#include "../Rendering/Renderer.h"
#include "../Files/Font/FontReader.h"
#include "../UI/TextComponent.h"
#include "../Particles/ParticleSystem.h"
#include "../Containers/TTypedTree.h"
#include "../Framework/Framework.h"
#include "../Framework/Project.h"
#include "../Framework/Scene.h"
#include "../Time/GameTime.h"
#include "../Camera/VirtualCamera.h"
#include "../Framework/SceneLoader.h"
#include "../Framework/PrefabLoader.h"
#include "../Files/LFileOperations.h"
#include "../../ThirdParty/Nameof/nameof.hpp"

Application::Application()
{
}


Application::~Application()
{
}

void Application::Run()
{
	TempProfiler* windowProfiler = new TempProfiler();
	Window newWindow;
	newWindow.InstantiateWindow();
	delete windowProfiler;

	Renderer tempRenderer;
	tempRenderer.MakeCurrent();

	GameTime::StartGame();

	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Scenes/TestScene.pbscene", 0);

	Scene::Activate(0);

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
		tempRenderer.LogRenderingError();
		tempRenderer.OnEndFrame();
		GameTime::OnEndFrame();
		Debug::log << "DeltaTime = " << GameTime::deltaTime << Debug::endl;
	}
	Debug::FlushToFile();
	std::cin.get();
}