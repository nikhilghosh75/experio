#include "EditorApplication.h"
#include <Windows.h>
#include <stdio.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "EditorWindow.h"
#include "Runtime/Core/Window.h"
#include "../Test Modules/TestModule.h"
#include "Runtime/Framework/SceneLoader.h"
#include "Runtime/Framework/Project.h"

typedef void(__cdecl *MYPROC)();

std::vector<EditorModule*> EditorApplication::modules;

EditorApplication::EditorApplication()
{
}

EditorApplication::~EditorApplication()
{
	for (int i = 0; i < modules.size(); i++)
	{
		delete modules[i];
	}
}

void EditorApplication::Run()
{
	EditorWindow::InitializeWindow();

	// TEMP
	LoadProject("C:/Users/debgh/source/repos/project-bloo/bin/x64/Debug/Demo Project/Demo Project.dll");
	modules.push_back(new TestModule());

	while (EditorWindow::isActive)
	{
		EditorWindow::BeginFrame();
		RenderModules();
		EditorWindow::EndFrame();
	}

	EditorWindow::CloseWindow();
}

void EditorApplication::LoadProject(std::string dllFilePath)
{
	HINSTANCE hinstLib;
	MYPROC ProcSetup, ProcRun;

	hinstLib = LoadLibrary(TEXT(dllFilePath.c_str()));

	if (hinstLib != NULL)
	{
		ProcSetup = (MYPROC)GetProcAddress(hinstLib, "SetupProject");

		if (NULL != ProcSetup)
		{
			(ProcSetup)();
		}
	}
}

void EditorApplication::RenderModules()
{
	for (int i = 0; i < modules.size(); i++)
	{
		modules[i]->Display();
	}
}
