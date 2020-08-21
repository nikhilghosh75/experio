#include "Scene.h"
#include "../Containers/TTypedTree.h"

Scene Scene::scenes[MAX_SCENES];
uint8_t Scene::sceneCount = 0;

Scene::Scene()
{
	this->name = "";
	this->id = sceneCount;
	this->sceneHiearchy = TTypedTree<GameObject>(GameObject());

	sceneCount++;
}

Scene::Scene(std::string name)
{
	this->name = name;
	this->id = sceneCount;
	this->sceneHiearchy = TTypedTree<GameObject>(GameObject((std::string)"Scene Root", 0, 0));

	sceneCount++;
}

void Scene::SetName(std::string name)
{
	this->name = name;
}

void Scene::Activate(uint8_t sceneIndex)
{
	scenes[sceneIndex].isActive = true;
}

void Scene::Deactivate(uint8_t sceneIndex)
{
	scenes[sceneIndex].isActive = false;
}

bool Scene::IsActive(GameObject * object)
{
	return Scene::scenes[object->sceneIndex].isActive;
}

bool Scene::IsActive(uint8_t sceneIndex)
{
	return Scene::scenes[sceneIndex].isActive;
}
