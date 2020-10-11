#include "Scene.h"
#include "../Containers/TTypedTree.h"

Scene Scene::scenes[MAX_SCENES];
uint8_t Scene::sceneCount = 0;

Scene::Scene()
{
	this->name = "";
	this->id = sceneCount;
	this->sceneRoot = GameObject((std::string)"Scene Root", 0, 0);

	sceneCount++;
}

Scene::Scene(std::string name)
{
	this->name = name;
	this->id = sceneCount;
	this->sceneRoot = GameObject((std::string)"Scene Root", 0, 0);

	sceneCount++;
}

void Scene::SetName(std::string name)
{
	this->name = name;
}

unsigned int Scene::GetNumGameObjects()
{
	int currentNum = 0;
	ForEach(&sceneRoot, [&currentNum](GameObject* object) { currentNum++; });
	return 0;
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

void Scene::ForAllActiveScenes(std::function<void(Scene)> func)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		if (Scene::scenes[i].isActive)
		{
			func(Scene::scenes[i]);
		}
	}
}

GameObject * Scene::FindGameObjectFromId(uint64_t id)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		GameObject* foundObject = GameObject::FindGameObjectOfID(id, i);
		if (foundObject != nullptr)
		{
			return foundObject;
		}
	}
	return nullptr;
}
