#pragma once
#include <vector>
#include <string>
#include "EditorModule.h"
#include "Runtime/Core/DllLoader.h"

class EditorProject;

class EditorApplication
{
	static std::vector<EditorModule*> modules;

	void(*beginFrameCallback)(float);
	void(*endFrameCallback)(float);

	friend class EditorProject;
public:
	static DllLoader loader;

	EditorApplication();
	~EditorApplication();

	void Setup(const std::string& projectFilepath);

	void LoadScenes();

	void Run();

	void Shutdown();

	void SetBeginFrameCallback(void(*callback)(float));
	void SetEndFrameCallback(void(*callback)(float));

	static std::string assetsFilePath;
	static std::string binariesFilePath;
	static std::string configFilePath;
	static std::string editorFilePath;
	static std::string generatedFilePath;
	static std::string sourceFilePath;

	static std::string experioFilePath;
	static std::string experioEditorFilePath;
	static std::string experioDependenciesFilePath;
	static std::string experioBinariesFilePath;
	static std::string standardAssetsFilePath;

	static std::string defaultScenePath;

	static std::string currentScenePath;

	static std::string GetShortenedFilePath(std::string& fullFilePath);

	static EditorModule* AddModule(EditorModule* module);

private:
	static void AddDefaultModules();

	void BeginFrame();

	void Update();

	void EndFrame();

	void RenderModules();
};
