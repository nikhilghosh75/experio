#include "GApplication.h"
#include "GWindow.h"
#include <iostream>
#include "../Debug/TempProfiler.h"
#include "../Rendering/Renderer.h"
#include "../Math/FVector3.h"
#include "../Math/FQuaternion.h"
#include "../Rendering/MeshData.h"
#include "../Rendering/FCameraData.h"
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

	FMeshData* cubeData = tempRenderer.TempSetup();
	FCameraData camera(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), 45.f);

	while (newWindow.isActive)
	{
		tempRenderer.OnNewFrame();
		newWindow.OnUpdate();
		//tempRenderer.TempRenderer();
		tempRenderer.DrawMesh(*cubeData, camera);
	}
	cin.get();
	delete cubeData;
}
