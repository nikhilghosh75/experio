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

	GameTime::StartGame();

	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Demo Project/Assets/Scenes/TestScene.pbscene", 0);

	Scene::Activate(0);
	GameObject cameraObject((std::string)"Camera", 1, 2);
	cameraObject.SetTransform(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), FVector3(1, 1, 1));

	VirtualCamera mainCamera(&cameraObject);
	mainCamera.fieldOfView = 45.f;
	mainCamera.Start();

	GameObject secondObject((std::string)"Second Object", 1, 2);
	secondObject.SetTransform(FVector3(5, 5, 5), FQuaternion(glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), FVector3(1, 1, 1));

	VirtualCamera secondCamera(&cameraObject);
	secondCamera.fieldOfView = 60.f;
	secondCamera.priority = -1.f;
	secondCamera.Start();

	while (newWindow.isActive)
	{
		tempRenderer.OnNewFrame();
		newWindow.OnUpdate();
		if (!newWindow.isActive)
		{
			break;
		}
		tempRenderer.Clear();
		//tempRenderer.TempFramebufferRenderer();
		Project::componentManager->Update();
		tempRenderer.LogRenderingError();
		tempRenderer.OnEndFrame();
		GameTime::OnEndFrame();
		Debug::Log("DeltaTime = " + std::to_string(GameTime::deltaTime));
	}
	std::cin.get();
}