#include "SceneLoader.h"
#include "../Files/LFileOperations.h"
#include "../Debug/Debug.h"
#include "AssetMap.h"
#include "Scene.h"
#include "Project.h"
#include "../Containers/THashtable.h"
#include "../Containers/TTypedTree.h"
#include "../Containers/LString.h"

extern std::vector<std::string> GetParamsList(unsigned int classId);

template<class T>
extern void SetComponentParams(std::vector<std::string> params, T* component);

template<class T>
extern void SetComponentBinaryParams(void* data, T* component);

extern void AddComponentToScene(unsigned int classId, std::vector<std::string> params, GameObject* gameObject, uint8_t sceneId);
extern void AddComponentToScene(unsigned int classId, void* params, size_t paramSize, GameObject* gameObject, uint8_t sceneId);

bool SceneLoader::LoadSceneFromFile(std::string filePath, int sceneSlot, ESceneProjectCompareType compareType)
{
	if (sceneSlot >= MAX_SCENES)
	{
		Debug::LogError("Invalid Scene");
		return false;
	}

	if (LFileOperations::DoesFileHaveExtension(filePath, "pbscene"))
	{
		return LoadSceneFromTextFile(filePath, sceneSlot, compareType);
	}
	if (LFileOperations::DoesFileHaveExtension(filePath, "pbbscene"))
	{
		return LoadSceneFromBinaryFile(filePath, sceneSlot);
	}
	Debug::LogError("Loaded Scene is an invalid scene file type");
	return false;
}

bool SceneLoader::LoadSceneFromTextFile(std::string filePath, int sceneSlot, ESceneProjectCompareType compareType)
{
	std::ifstream sceneFile(filePath);
	if (sceneFile.fail())
	{
		Debug::LogError("File " + filePath + " could not be opened");
		return false;
	}

	char word[256];

	// Check First Line
	sceneFile.getline(word, 256);
	if (strcmp(word, "PROJECT BLOO SCENE") != 0)
	{
		Debug::LogError("File " + filePath + " is improperly formatted");
		return false;
	}
	Scene* currentScene = &Scene::scenes[sceneSlot];

	// Scene sceneName to name
	sceneFile >> word;
	sceneFile.getline(word, 256);
	Scene::scenes[sceneSlot].SetName(std::string(word));

	// Maybe Check Project Name
	sceneFile >> word;
	sceneFile.getline(word, 256);
	if (ShouldQuitOnProjectName((std::string)word, compareType)) return false;

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
				currentNode->name = (std::string)(&word[1]); // Account for space
				currentNode->sceneIndex = sceneSlot;
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
	currentScene->isLoaded = true;
	Scene::filepaths[sceneSlot] = filePath;
	Debug::Log("Scene Loading Finished");
	return true;
}

bool SceneLoader::LoadSceneFromBinaryFile(std::string filePath, int sceneSlot)
{
	std::ifstream sceneFile(filePath, std::ios::binary);
	if (sceneFile.fail())
	{
		Debug::LogError("File " + filePath + " could not be opened");
		return false;
	}

	uint32_t currentPosition = 0;

	// Evalutate Check
	char check[9];
	sceneFile.read(check, 8);
	currentPosition += 8;
	check[8] = 0; // Null character
	if (strcmp(check, "PBBSCENE") != 0)
	{
		Debug::LogError("Binary Scene is invalid");
		return false;
	}

	Scene& currentScene = Scene::scenes[sceneSlot];

	// Parse Header
	char header[28];
	sceneFile.read(header, 28);
	currentPosition += 28;
	uint32_t gameObjectOffset = *(uint32_t*)&(header[4]);
	uint32_t componentOffset = *(uint32_t*)&(header[8]);
	uint32_t datafileID = *(uint32_t*)&(header[12]);
	uint32_t numComponents = *(uint32_t*)&(header[20]);
	uint32_t numGameObjects = *(uint32_t*)&(header[24]);

	LoadSceneData(datafileID);

	// Parse Name
	char name[32];
	sceneFile.read(name, 32);
	currentPosition += 32;
	currentScene.SetName(std::string(name));

	THashtable<uint32_t, GameObject*> gameObjects;
	gameObjects.Resize(numGameObjects / 3);

	// Parse GameObject
	for (uint32_t i = 0; i < numGameObjects; i++)
	{
		char gameObjectHeader[56];
		sceneFile.read(gameObjectHeader, 56);
		currentPosition += 56;

		// Parse Game Object Header
		uint8_t nameLength = *(uint8_t*)&(header[0]);
		uint8_t layer = *(uint8_t*)&(header[1]);
		uint16_t tag = *(uint16_t*)&(header[2]);
		uint32_t parentID = *(uint32_t*)&(header[4]);
		uint8_t numChildren = *(uint8_t*)&(header[8]);
		bool isActive = *(bool*)&(header[9]);
		FVector3 position = *(FVector3*)&(header[12]);
		FQuaternion rotation = *(FQuaternion*)&(header[24]);
		FVector3 scale = *(FVector3*)&(header[40]);
		uint32_t gameObjectID = *(uint32_t*)&(header[52]);

		char gameObjectName[128];
		sceneFile.read(gameObjectName, nameLength);
		currentPosition += nameLength;
		gameObjectName[nameLength] = 0; // Ensure null terminator

		GameObject* currentGameObject = nullptr;
		if (i == 0) // Scene Root
		{
			currentGameObject = &(currentScene.sceneRoot);
			currentGameObject->name = "Scene Root";
		}
		else
		{
			GameObject* parent = gameObjects.Get(parentID);
			currentGameObject = parent->AddChild(std::string(gameObjectName));
		}

		currentGameObject->sceneIndex = sceneSlot;
		currentGameObject->layer = layer;
		currentGameObject->tag = tag;
		currentGameObject->ReserveChildren(numChildren);
		currentGameObject->isActive = isActive;
		currentGameObject->localPosition = position;
		currentGameObject->localRotation = rotation;
		currentGameObject->localScale = scale;

		gameObjects.Insert(gameObjectID, currentGameObject);
	}

	// Parse Components
	for (int i = 0; i < numComponents; i++)
	{
		char componentHeader[12];
		sceneFile.read(componentHeader, 12);
		currentPosition += 12;

		uint32_t classID = *(uint32_t*)&(componentHeader[0]);
		uint32_t gameObjectID = *(uint32_t*)&(componentHeader[4]);
		uint16_t paramAmount = *(uint16_t*)&(componentHeader[8]);
		uint16_t paramSize = *(uint16_t*)&(componentHeader[10]);

		char componentParams[4096];
		sceneFile.read(componentParams, paramSize);
		currentPosition += paramSize;

		GameObject* componentObject = gameObjects.Get(gameObjectID);
		AddComponentToScene(classID, componentParams, paramSize, componentObject, sceneSlot);
	}
	delete Scene::sceneData;
	Scene::sceneData = nullptr;

	currentScene.isActive = true;
	currentScene.isLoaded = true;
	Scene::filepaths[sceneSlot] = filePath;
	Debug::Log("Scene Loading Finished");

	return true;
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
			Debug::LogError("Scene does not have the same project name as the project. Exiting scene loading process");
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
	if (strcmp(word, "[]") == 0)
	{
		return;
	}
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

void SceneLoader::LoadSceneData(uint32_t dataIndex)
{
	if (dataIndex == 0)
		return;

	std::string filepath = AssetMap::assetMap.Get(dataIndex);
	std::ifstream dataFile(filepath);

	if (dataFile.fail())
	{
		Debug::LogError("Data File could not be loaded");
		return;
	}

	char check[9];
	dataFile.read(check, 8);
	check[8] = 0;

	if (strcmp(check, "PBSCDATA") != 0)
	{
		Debug::LogError("Invalid Scene Data File Format");
		return;
	}

	char header[12];
	dataFile.read(header, 12);
	
	uint32_t numElements = *(uint32_t*)&(header[0]);
	uint32_t sizeOf = *(uint32_t*)&(header[0]);
	Scene::sceneData = malloc(sizeOf); // Change Later
	dataFile.read((char*)Scene::sceneData, sizeOf);
}
