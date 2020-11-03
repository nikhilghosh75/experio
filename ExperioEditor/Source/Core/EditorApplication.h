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

	void Shutdown();

	void SetBeginFrameCallback(void(*callback)(float));
	void SetEndFrameCallback(void(*callback)(float));

	void LoadProject(std::string dllFilePath); // Change Later

	static std::string assetsFilePath;
	static std::string configFilePath;
	static std::string scriptsFilePath;
	static std::string standardAssetsFilePath;

	static std::string GetShortenedFilePath(std::string& fullFilePath);

	template<class Module>
	static void AddModule();

private:
	void TempSetup();

	void BeginFrame();
	void EndFrame();

	void RenderModules();
};
