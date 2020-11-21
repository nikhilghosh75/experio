#include "Scene.h"
#include "../Containers/TTypedTree.h"

Scene Scene::scenes[MAX_SCENES];
std::string Scene::filepaths[MAX_SCENES];
uint8_t Scene::sceneCount = 0;
void* Scene::sceneData = nullptr;

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

bool Scene::IsLoaded(uint8_t sceneIndex)
{
	return Scene::scenes[sceneIndex].isLoaded;
}

bool Scene::IsSceneLoaded(const std::string & name)
{
	for (uint8_t i = 0; i < MAX_SCENES; i++)
	{
		if (Scene::scenes[i].name == name) return true;
	}
	return false;
}

bool Scene::IsSceneAtFilepathLoaded(const std::string & filepath)
{
	for (uint8_t i = 0; i < MAX_SCENES; i++)
	{
		if (Scene::filepaths[i] == filepath) return true;
	}
	return false;
}

void Scene::UnloadScene(uint8_t sceneIndex)
{
	if (!Scene::scenes[sceneIndex].isLoaded)
	{
		return;
	}
	
	GameObject& sceneRoot = Scene::scenes[sceneIndex].sceneRoot;
	if (sceneRoot.children.size() != 0)
	{
		for (int i = 0; i < sceneRoot.children.size(); i++)
		{
			delete sceneRoot.children[i];
		}
		int n = sceneRoot.children.size();
		for (int i = 0; i < n; i++)
		{
			sceneRoot.children.pop_back();
		}
	}
	Scene::scenes[sceneIndex].isActive = false;
	Scene::scenes[sceneIndex].isLoaded = false;
	Scene::scenes[sceneIndex].name = "";
}

void Scene::UnloadAllScenes()
{
	for (uint8_t i = 0; i < MAX_SCENES; i++)
	{
		UnloadScene(i);
	}
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

void Scene::UpdateGameObject(GameObject & object)
{
	GameObject* foundObject = FindGameObjectFromId(object.id);

	foundObject->localPosition = object.localPosition;
	foundObject->localRotation = object.localRotation;
	foundObject->localScale = object.localScale;
}
