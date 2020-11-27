#include "SceneConverter.h"
#include "../BuildSystem/AssetMapSaver.h"
#include "Runtime\Containers\THashtable.h"
#include "Runtime\Debug\Debug.h"
#include "Runtime\Files\LFileOperations.h"
#include "Runtime\Framework\Project.h"
#include "Runtime\Framework\Scene.h"
#include "Runtime\Framework\SceneLoader.h"
#include <fstream>

const uint32_t sizeOfBaseGameObject = 56;

extern void SaveBinaryComponentToScene(unsigned int componentID, Component* component, std::ofstream& stream);

extern size_t SerializedSizeOfComponent(unsigned int classId);

extern std::vector<std::string> GetParamsList(unsigned int classId);

uint32_t SizeOfGameObject(const GameObject* object)
{
	return sizeOfBaseGameObject + object->name.size();
}

void SceneConverter::ConvertSceneToBinary(const std::string & fromFilepath, const std::string & toFilepath)
{
	if (!LFileOperations::DoesFileHaveExtension(fromFilepath, ".pbscene"))
	{
		Debug::LogError("From Filepath is not a correct filepath");
		return;
	}

	if (!LFileOperations::DoesFileHaveExtension(toFilepath, ".pbbscene"))
	{
		Debug::LogError("To Filepath is not a correct filepath");
		return;
	}

	// Load From Filepath
	if (!Scene::IsSceneAtFilepathLoaded(fromFilepath))
	{
		SceneLoader::LoadSceneFromFile(fromFilepath, MAX_SCENES - 3);
	}

	Scene& currentScene = Scene::scenes[MAX_SCENES - 3];

	std::ofstream outFile(toFilepath, std::ios::out | std::ios::binary);

	outFile.write("PBBSCENE", 8);
	outFile.write("0000", 4); // Bytes 8-11

	uint32_t sizeOfGameObjects = 0;
	ForEach(&currentScene.sceneRoot, [&sizeOfGameObjects](GameObject* object) {
		sizeOfGameObjects += sizeOfBaseGameObject + object->name.size();
	});

	uint32_t gameObjectOffset = 68;
	uint32_t componentsOffset = gameObjectOffset + sizeOfGameObjects;
	uint32_t sceneDataAssetID = AssetMapSaver::NextAssetMapIndex();
	uint32_t numComponents = Project::componentManager->ComponentCount();
	uint32_t numGameObjects = currentScene.GetNumGameObjects();

	outFile.write((char*)&gameObjectOffset, 4);
	outFile.write((char*)&componentsOffset, 4);
	outFile.write((char*)&sceneDataAssetID, 4);
	outFile.write("0000", 4);
	outFile.write((char*)&numComponents, 4);
	outFile.write((char*)&numGameObjects, 4);
	
	outFile.write(currentScene.GetName().c_str(), 32);

	THashtable<GameObject*, uint32_t, PointerHashFunction<GameObject>> indexes;
	uint32_t gameObjectindex = 0;

	// Serialize Game Objects
	ForEach(&currentScene.sceneRoot, 
	[&outFile, &indexes, &gameObjectindex](GameObject* gameObject) 
	{
		uint8_t nameLength = gameObject->name.size();
		uint8_t layer = gameObject->layer;
		uint16_t tag = gameObject->tag;
		uint32_t parentIndex = 0;
		if (gameObject->parent != nullptr)
		{
			parentIndex = indexes.Get(gameObject->parent);
		}
		uint8_t numChildren = gameObject->children.size();
		bool isActive = gameObject->isActive;
		FVector3 position = gameObject->localPosition;
		FQuaternion rotation = gameObject->localRotation;
		FVector3 scale = gameObject->localScale;
		uint32_t id = gameObjectindex;

		outFile.write((char*)&nameLength, 1);
		outFile.write((char*)&layer, 1);
		outFile.write((char*)&tag, 2);
		outFile.write((char*)&parentIndex, 4);
		outFile.write((char*)&numChildren, 1);
		outFile.write((char*)&isActive, 1);
		outFile.write("00", 2);
		outFile.write((char*)&position, 12);
		outFile.write((char*)&rotation, 16);
		outFile.write((char*)&scale, 12);
		outFile.write((char*)&id, 4);

		outFile.write(gameObject->name.c_str(), nameLength);

		indexes.Insert(gameObject, gameObjectindex);
		gameObjectindex++;
	});

	std::vector<Component*> components;
	std::vector<unsigned int> componentIds;

	Project::componentManager->GetAllComponents(components, componentIds, MAX_SCENES - 3);
	for (size_t i = 0; i < components.size(); i++)
	{
		outFile.write((char*)&(componentIds[i]), 4);

		uint32_t indexOfGameObject = indexes.Get(components[i]->GetGameObject());
		outFile.write((char*)&(indexOfGameObject), 4);

		uint16_t paramAmount = GetParamsList(componentIds[i]).size();
		outFile.write((char*)&(paramAmount), 2);

		uint16_t componentSize = SerializedSizeOfComponent(componentIds[i]);
		outFile.write((char*)&(componentSize), 2);

		SaveBinaryComponentToScene(componentIds[i], components[i], outFile);
	}

	outFile.close();
	Scene::UnloadScene(MAX_SCENES - 3);
}
