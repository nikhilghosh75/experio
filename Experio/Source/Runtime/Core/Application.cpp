#include "Application.h"
#include "GWindow.h"
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
using namespace std;

Application::Application()
{
}


Application::~Application()
{
}

void Application::Run()
{
	TempProfiler* windowProfiler = new TempProfiler();
	GWindow newWindow;
	newWindow.InstantiateWindow();
	delete windowProfiler;
	Renderer tempRenderer;

	Project::componentManager = new TestComponentManager();

	GameTime::StartGame();

	TTypedTreeTest();

	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Amber/Assets/Scenes/TestScene.pbscene", 0);

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

	glm::mat4 test = glm::perspective(0.785f, 2.589f, 0.1f, 1000.f);

	/*
	FontData* data = FontReader::ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Fonts/calibri.fnt");
	TextComponent textComponent;
	textComponent.fontSize = 72;
	textComponent.font = data;
	textComponent.shader = new Shader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DFragment.shader");
	textComponent.text = "Nikhil Ghosh";
	textComponent.transform = RectTransform(FVector2(0.4f, 0.4f), FVector2(1.f, 0.6f));

	GameObject testObject((std::string)"Test", 0, 1);
	GameObject billboardObject((std::string)"Billboard", 0, 1);
	billboardObject.transform = FTransform(0, 2, 0);
	GameObject meshObject((std::string)"Mesh", 0, 1);
	meshObject.transform = FTransform(0, -0.5, 0, 0, 0.70711, 0, 0.70711, 1.5, 1.5, 1.5);

	Component* billboard = Project::componentManager->AddComponent(&billboardObject, 103);
	billboard->Start();
	Component* mesh = Project::componentManager->AddComponent(&meshObject, 101);
	mesh->Start();
	*/

	while (newWindow.isActive)
	{
		tempRenderer.OnNewFrame();
		newWindow.OnUpdate();
		tempRenderer.Clear();
		//tempRenderer.TempRenderer();
		Project::componentManager->Update();
		tempRenderer.LogRenderingError();
		GameTime::OnEndFrame();
		GDebug::Log("DeltaTime = " + to_string(GameTime::deltaTime));
	}
	cin.get();
}