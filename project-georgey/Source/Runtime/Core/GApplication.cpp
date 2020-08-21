#include "GApplication.h"
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
#include "../Camera/Camera.h"
#include "../Framework/SceneLoader.h"

#include "../Files/LFileOperations.h"
using namespace std;

GApplication::GApplication()
{
}


GApplication::~GApplication()
{
}

void GApplication::Run()
{
	TempProfiler* windowProfiler = new TempProfiler();
	GWindow newWindow;
	newWindow.InstantiateWindow();
	delete windowProfiler;
	Renderer tempRenderer;

	Project::componentManager = new TestComponentManager();

	GameTime::StartGame();

	TTypedTreeTest();

	std::string test = LFileOperations::GetFullFilePath("?Standard?/Textures/HealthBar.bmp");

	SceneLoader::LoadSceneFromFile("C:/Users/debgh/source/repos/project-bloo/Amber/Assets/Scenes/TestScene.pbscene", 0);

	Scene::Activate(0);

	/*
	GameObject cameraObject((std::string)"Camera", 1, 2);
	cameraObject.transform = FTransform(FVector3(4.f, 3.f, -3.f), FQuaternion::LookAt(FVector3(4.f, 3.f, -3.f), FVector3(0.f, 0.f, 0.f), FVector3(0.f, 1.f, 0.f)));

	Camera mainCamera(&cameraObject);
	mainCamera.fieldOfView = 45.f;

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
		Project::componentManager->Update();
		// textComponent.RenderText();
		tempRenderer.LogRenderingError();
		GameTime::OnEndFrame();
		GDebug::Log("DeltaTime = " + to_string(GameTime::deltaTime));
	}
	cin.get();
}