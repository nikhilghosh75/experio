#pragma once

#include "../Containers/TTypedTree.h"
#include "GameObject.h"
#include "Component.h"
#include <functional>
#include <string>

#define MAX_SCENES 32

class Scene
{
public:
	GameObject sceneRoot;
	bool isActive = false;

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

	static Scene scenes[MAX_SCENES];
	static uint8_t sceneCount;

	static void Activate(uint8_t sceneIndex);
	static void Deactivate(uint8_t sceneIndex);

	static bool IsActive(GameObject* object);
	static bool IsActive(uint8_t sceneIndex);

	static void ForAllActiveScenes(std::function<void(Scene)> func);

	static GameObject* FindGameObjectFromId(uint64_t id);

	static void UpdateGameObject(GameObject& object);
};