#pragma once
#include <vector>
#include <string>
#include "EditorModule.h"
#include "Runtime/Core/DllLoader.h"

class EditorApplication
{
	static std::vector<EditorModule*> modules;
public:
	static DllLoader loader;

	EditorApplication();
	~EditorApplication();

	void Run();

	void LoadProject(std::string dllFilePath); // Change Later

private:
	void RenderModules();
};