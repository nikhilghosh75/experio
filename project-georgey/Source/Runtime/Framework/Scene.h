#pragma once

#include "../Containers/TTypedTree.h"
#include "GameObject.h"
#include "Component.h"
#include "ComponentManager.h"
#include <string>

class Scene
{
public:
	TTypedTree<GameObject> sceneHiearchy;

private:
	ComponentManager* componentManager;
	std::string name;
	unsigned short id;
public:
	Scene(std::string name, ComponentManager* manager);

	std::string GetName() const { return name; }

	static Scene* scenes[32];
	static uint8_t sceneCount;
};