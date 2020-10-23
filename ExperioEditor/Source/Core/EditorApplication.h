#pragma once
#include <vector>
#include <string>
#include "EditorModule.h"
#include "Runtime/Core/DllLoader.h"

class EditorApplication
{
	static std::vector<EditorModule*> modules;

	void(*beginFrameCallback)(float);
	void(*endFrameCallback)(float);
public:
	static DllLoader loader;

	EditorApplication();
	~EditorApplication();

	void Setup();

	void Run();

	void SetBeginFrameCallback(void(*callback)(float));
	void SetEndFrameCallback(void(*callback)(float));

	void LoadProject(std::string dllFilePath); // Change Later

private:
	void BeginFrame();
	void EndFrame();

	void RenderModules();
};