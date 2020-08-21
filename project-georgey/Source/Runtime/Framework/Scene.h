#pragma once

#include "../Containers/TTypedTree.h"
#include "GameObject.h"
#include "Component.h"
#include <string>

#define MAX_SCENES 32

class Scene
{
public:
	TTypedTree<GameObject> sceneHiearchy;
	bool isActive = false;

private:
	std::string name;
	unsigned short id;
public:
	Scene();
	Scene(std::string name);

	std::string GetName() const { return name; }
	void SetName(std::string name);

	static Scene scenes[MAX_SCENES];
	static uint8_t sceneCount;

	static void Activate(uint8_t sceneIndex);
	static void Deactivate(uint8_t sceneIndex);

	static bool IsActive(GameObject* object);
	static bool IsActive(uint8_t sceneIndex);
};