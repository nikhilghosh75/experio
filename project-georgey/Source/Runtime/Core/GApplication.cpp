#include "GApplication.h"
#include "GWindow.h"
#include <iostream>
#include "../Debug/TempProfiler.h"
#include "../Rendering/Renderer.h"
#include "../Math/FVector3.h"
#include "../Math/FQuaternion.h"
#include "../Camera/FCameraData.h"
#include "../Files/Mesh/OBJReader.h"
#include "../Rendering/MeshComponent.h"
#include "../Rendering/Texture.h"
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

	while (newWindow.isActive)
	{
		tempRenderer.OnNewFrame();
		newWindow.OnUpdate();
		tempRenderer.Clear();
		tempRenderer.TempRenderer();
		//tempRenderer.TempModelRenderer();
	}
	cin.get();
}
