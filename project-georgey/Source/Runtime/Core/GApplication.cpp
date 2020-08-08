#include "GApplication.h"
#include "GWindow.h"
#include <iostream>
#include "../Debug/TempProfiler.h"
#include "../Rendering/Renderer.h"
#include "../Files/Font/FNTReader.h"
#include "../UI/TextComponent.h"
#include "../Particles/ParticleSystem.h"
#include "../Containers/TTypedTree.h"
#include "../Framework/Component.h"
#include "../Framework/Project.h"
#include "../Time/GameTime.h"
#include "../Camera/Camera.h"
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

	GameObject cameraObject(&(std::string)"Camera", 1, 2);
	cameraObject.transform = FTransform(FVector3(4.f, 3.f, -3.f), FQuaternion::LookAt(FVector3(4.f, 3.f, -3.f), FVector3(0.f, 0.f, 0.f), FVector3(0.f, 1.f, 0.f)));

	Camera mainCamera(&cameraObject);
	mainCamera.fieldOfView = 45.f;

	FNTReader reader;
	FontData* data = reader.ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Fonts/calibri.fnt");
	TextComponent textComponent;
	textComponent.fontSize = 72;
	textComponent.font = data;
	textComponent.shader = new Shader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DFragment.shader");
	textComponent.text = "Nikhil Ghosh";
	textComponent.transform = RectTransform(FVector2(0.4f, 0.4f), FVector2(1.f, 0.6f));

	GameObject testObject(&(std::string)"Test", 0, 1);

	unsigned int test = Project::ClassTypeToInt<TestComponent>();

	//Project::componentManager->AddComponent(&testObject, 102);
	Project::componentManager->AddComponent(&testObject, 103);
	Project::componentManager->AddComponent(&testObject, 101);

	while (newWindow.isActive)
	{
		tempRenderer.OnNewFrame();
		newWindow.OnUpdate();
		tempRenderer.Clear();
		//tempRenderer.TempRenderer();
		Project::componentManager->Update();
		textComponent.RenderText();
		tempRenderer.LogRenderingError();
		GameTime::OnEndFrame();
		GDebug::Log("DeltaTime = " + to_string(GameTime::deltaTime));
	}
	cin.get();
}