#include "SceneSaver.h"
#include "Runtime/Framework/Framework.h"
#include <fstream>

bool SceneSaver::SaveScene(uint8_t sceneIndex, const std::string& filename)
{
	if (sceneIndex >= MAX_SCENES)
	{
		Debug::LogError("Invalid Scene");
		return false;
	}
	if (!Scene::IsLoaded(sceneIndex))
	{
		Debug::errorLog << "Scene at index " << sceneIndex << " is not loaded" << Debug::endl;
		return false;
	}
	if (!LFileOperations::DoesFileHaveExtension(filename, ".pbscene"))
	{
		Debug::LogError("Loaded Scene is not a .pbscene file");
		return false;
	}

	std::ofstream sceneFile(filename);
	if (sceneFile.fail())
	{
		Debug::LogError("File " + filename + " could not be opened");
		return false;
	}

	sceneFile << "PROJECT BLOO SCENE" << std::endl;
	sceneFile << "Name: " << "Test Scene" << std::endl; // Fix This
	sceneFile << "Project: " << Project::projectName << std::endl;

	return true;
}
