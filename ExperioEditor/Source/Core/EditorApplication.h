#pragma once
#include <vector>
#include <string>
#include "EditorModule.h"

class EditorApplication
{
	static std::vector<EditorModule*> modules;
public:
	EditorApplication();
	~EditorApplication();

	void Run();

	void LoadProject(std::string dllFilePath); // Change Later

private:
	void RenderModules();
};