#include "SceneLoader.h"
#include "../Files/LFileOperations.h"
#include "../Debug/Debug.h"
#include "Scene.h"
#include "Project.h"
#include "../Containers/TTypedTree.h"
#include "../Containers/LString.h"

extern std::vector<std::string> GetParamsList(unsigned int classId);

template<class T>
extern void SetComponentParams(std::vector<std::string> params, T* component);

extern void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId);

void SceneLoader::LoadSceneFromFile(std::string filePath, int sceneSlot, ESceneProjectCompareType compareType)
{
	if (sceneSlot >= MAX_SCENES)
	{
		Debug::LogError("Invalid Scene");
		return;
	}

	if (!LFileOperations::DoesFileHaveExtension(filePath, "pbscene"))
	{
		Debug::LogError("Loaded Scene is not a .pbscene file");
		return;
	}

	std::ifstream sceneFile(filePath);
	if (sceneFile.fail())
	{
		Debug::LogError("File " + filePath + " could not be opened");
		return;
	}

	char word[256];

	// Check First Line
	sceneFile.getline(word, 256);
	if (strcmp(word, "PROJECT BLOO SCENE") != 0)
	{
		Debug::LogError("File " + filePath + " is improperly formatted");
		return;
	}
	Scene* currentScene = &Scene::scenes[sceneSlot];

	// Scene sceneName to name
	sceneFile >> word;
	sceneFile.getline(word, 256);
	Scene::scenes[sceneSlot].SetName(std::string(word));

	// Maybe Check Project Name
	sceneFile >> word;
	sceneFile.getline(word, 256);
	if (ShouldQuitOnProjectName((std::string)word, compareType)) return;

	GameObject* currentNode = nullptr;
	bool isRoot = true;
	bool inComponent = false;

	while (sceneFile >> word)
	{
		if (strcmp(word, "{") == 0 || strcmp(word, "[{") == 0)
		{
			sceneFile >> word;
		}

		// Switch on Type
		if (strcmp(word, "Name:") == 0)
		{
			sceneFile.getline(word, 256);
			if (isRoot)
			{
				currentNode = &currentScene->sceneRoot;
				currentNode->name = (std::string)(&word[1]);
				isRoot = false;
			}
			else
			{
				currentNode = currentNode->AddChild((std::string)(&word[1]));
			}
		}
		else if (strcmp(word, "Transform:") == 0)
		{
			float w, x, y, z;
			
			// Position
			sceneFile >> x;
			sceneFile >> y;
			sceneFile >> z;
			currentNode->localPosition = FVector3(x, y, z);

			// Rotation
			sceneFile >> x;
			sceneFile >> y;
			sceneFile >> z;
			sceneFile >> w;
			currentNode->localRotation = FQuaternion(x, y, z, w);

			// Scale
			sceneFile >> x;
			sceneFile >> y;
			sceneFile >> z;
			currentNode->localScale = FVector3(x, y, z);
		}
		else if (strcmp(word, "Tag:") == 0)
		{
			int tag;
			sceneFile >> tag;
			currentNode->tag = tag;
		}
		else if (strcmp(word, "Layer:") == 0)
		{
			int layer;
			sceneFile >> layer;
			currentNode->layer = layer;
		}
		else if (strcmp(word, "Components:") == 0)
		{
			inComponent = true;
			AddComponentsToObjects(sceneFile, sceneSlot, currentNode);
			inComponent = false;
		}
		else if (strcmp(word, "Children:") == 0)
		{
			sceneFile >> word;
		}
		else if (strcmp(word, "},{") == 0)
		{
			currentNode = currentNode->parent;
		}
	}
	currentScene->isActive = true;
	Debug::Log("Scene Loading Finished");
}

bool SceneLoader::ShouldQuitOnProjectName(std::string sceneProjectName, ESceneProjectCompareType compareType)
{
	switch (compareType)
	{
	case ESceneProjectCompareType::None:
		return false;
	case ESceneProjectCompareType::Return:
		if (sceneProjectName != Project::projectName)
		{
			Debug::LogError("Scene does not have the same project name as the project. Exitting scene loading process");
			return true;
		}
		return false;
	case ESceneProjectCompareType::Warning:
		if (sceneProjectName != Project::projectName)
		{
			Debug::LogWarning("Scene does not have the same project name as the project. Make sure this is intentional");
		}
		return false;
	}
	return false;
}

void SceneLoader::AddComponentsToObjects(std::ifstream& stream, int sceneSlot, GameObject * gameObject)
{
	char word[256];

	stream >> word;
	while (strcmp(word, "}]") != 0)
	{
		unsigned int classID, numParams;

		// Get ClassID
		stream >> word;
		stream >> classID;

		std::vector<std::string> paramList = GetParamsList(classID);

		stream >> word;
		std::vector<std::string> params;
		params.reserve(paramList.size());

		for (int i = 0; i < paramList.size(); i++)
		{
			stream >> word;
			stream.getline(word, 256);
			params.emplace_back(word);
		}
		AddComponentToScene(classID, params, gameObject, sceneSlot);
		stream >> word;
	}
}
