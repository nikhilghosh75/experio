#include "PrefabLoader.h"
#include "Scene.h"
#include "../Files/LFileOperations.h"

extern std::vector<std::string> GetParamsList(unsigned int classId);

template<class T>
extern void SetComponentParams(std::vector<std::string> params, T* component);

extern void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId);

GameObject * PrefabLoader::LoadPrefab(std::string fileName, GameObject * parent)
{
	return LoadPrefab(fileName, parent, FVector3(0, 0, 0), FQuaternion());
}

GameObject * PrefabLoader::LoadPrefab(std::string fileName, GameObject * parent, FVector3 localPosition)
{
	return LoadPrefab(fileName, parent, localPosition, FQuaternion());
}

GameObject * PrefabLoader::LoadPrefab(std::string filePath, GameObject * parent, FVector3 localPosition, FQuaternion localRotation)
{
	if (!LFileOperations::DoesFileHaveExtension(filePath, "prefab"))
	{
		Debug::LogError("Prefab is not a .prefab file");
		return nullptr;
	}

	GameObject* currentObject = parent;
	bool isRoot = true;
	bool inComponent = false;
	GameObject* prefabRoot = nullptr;

	std::ifstream prefabFile(filePath);
	if (prefabFile.fail())
	{
		Debug::LogError("File " + filePath + " could not be opened");
		return nullptr;
	}

	Scene* currentScene = &(Scene::scenes[parent->sceneIndex]);
	char word[256];

	while (prefabFile >> word)
	{
		if (strcmp(word, "{") == 0 || strcmp(word, "[{") == 0)
		{
			prefabFile >> word;
		}

		// Switch on Type
		if (strcmp(word, "Name:") == 0)
		{
			prefabFile.getline(word, 256);
			{
				currentObject = currentObject->AddChild((std::string)word);
				if (isRoot)
				{
					isRoot = false;
					prefabRoot = currentObject;
				}
			}
		}
		else if (strcmp(word, "Transform:") == 0)
		{
			float w, x, y, z;

			// Position
			prefabFile >> x;
			prefabFile >> y;
			prefabFile >> z;
			currentObject->localPosition = FVector3(x, y, z);

			// Rotation
			prefabFile >> x;
			prefabFile >> y;
			prefabFile >> z;
			prefabFile >> w;
			currentObject->localRotation = FQuaternion(x, y, z, w);

			// Scale
			prefabFile >> x;
			prefabFile >> y;
			prefabFile >> z;
			currentObject->localScale = FVector3(x, y, z);
		}
		else if (strcmp(word, "Tag:") == 0)
		{
			int tag;
			prefabFile >> tag;
			currentObject->tag = tag;
		}
		else if (strcmp(word, "Layer:") == 0)
		{
			int layer;
			prefabFile >> layer;
			currentObject->layer = layer;
		}
		else if (strcmp(word, "Components:") == 0)
		{
			inComponent = true;
			AddComponentsToObject(prefabFile, currentObject);
			inComponent = false;
		}
		else if (strcmp(word, "Children:") == 0)
		{
			prefabFile >> word;
		}
		else if (strcmp(word, "},{") == 0)
		{
			currentObject = currentObject->parent;
		}
	}
	currentScene->isActive = true;
	Debug::Log("Scene Loading Finished");

	return prefabRoot;
}

void PrefabLoader::AddComponentsToObject(std::ifstream & stream, GameObject * gameObject)
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
		AddComponentToScene(classID, params, gameObject, gameObject->sceneIndex);
		stream >> word;
	}
}
