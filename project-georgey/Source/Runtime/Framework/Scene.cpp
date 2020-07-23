#include "Scene.h"

Scene* Scene::scenes[32];
uint8_t Scene::sceneCount = 0;

Scene::Scene(std::string name, ComponentManager * manager)
{
	this->name = name;
	this->componentManager = manager;
	this->id = sceneCount;

	sceneCount++;
}