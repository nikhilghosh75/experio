#pragma once

#include "../Containers/TArray.h"
#include "../Containers/TTypedTree.h"
#include "GameObject.h"
#include "Component.h"
#include <functional>
#include <stdint.h>
#include <string>

#define MAX_SCENES 32

/// <summary>
/// A class representing a scene in Experio.
/// All the scenes are stored in a static vector of scenes
/// A static 
/// Reserved Scenes:
///		29 (MAX_SCENES - 3) - Scene Conversions(in - editor only)
/// </summary>

class Scene
{
public:
	GameObject sceneRoot;
	bool isActive = false;
	bool isLoaded = false;

private:
	std::string name;
	uint8_t id;
public:
	Scene();
	Scene(std::string name);

	std::string GetName() const { return name; }
	void SetName(std::string name);

	uint8_t GetId() const { return id; }

	unsigned int GetNumGameObjects();

	size_t GetNumComponents();

	size_t SizeOf();
	
	template<typename T>
	TArray<T*> GetAllComponents() const;

	static Scene scenes[MAX_SCENES];
	static std::string filepaths[MAX_SCENES];
	static uint8_t sceneCount;

	static void* sceneData;

	static void Activate(uint8_t sceneIndex);
	static void Deactivate(uint8_t sceneIndex);

	static bool IsActive(GameObject* object);
	static bool IsActive(uint8_t sceneIndex);

	static bool IsLoaded(uint8_t sceneIndex);

	static bool IsSceneLoaded(const std::string& name);

	static bool IsSceneAtFilepathLoaded(const std::string& filepath);

	static uint8_t IndexOfLoadedScene(const std::string& filepath);

	static void LoadBlankScene(uint8_t sceneIndex);

	static void UnloadScene(uint8_t sceneIndex);

	static void UnloadAllScenes();

	static void ForAllActiveScenes(std::function<void(Scene&)> func);

	static GameObject* FindGameObjectFromId(uint64_t id);

	static void UpdateGameObject(GameObject& object);

	static size_t SizeOfLoadedScenes();
};

#include "Project.h"

template<typename T>
inline TArray<T*> Scene::GetAllComponents() const
{
	std::vector<Component*> components;
	std::vector<unsigned int> componentIds;
	Project::componentManager->GetAllComponents(components, componentIds, this->id);

	TArray<T*> returnArray;
	unsigned int typeId = Project::ClassTypeToInt<T>();
	for (size_t i = 0; i < components.size(); i++)
	{
		if (componentIds[i] == typeId)
		{
			returnArray.Append((T*)components[i]);
		}
	}

	return returnArray;
}