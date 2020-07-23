#include "GameObject.h"
#include "Project.h"

GameObject::GameObject(std::string * name)
{
	this->name = name;
	this->tag = 0;
	this->layer = 0;
	this->sceneIndex = 0;
}

GameObject::GameObject(std::string * name, unsigned short tag, uint8_t layer)
{
	this->name = name;
	this->tag = tag;
	this->layer = layer;
	this->sceneIndex = 0;
}

GameObject::GameObject(std::string * name, unsigned short tag, uint8_t layer, uint8_t scene)
{
	this->name = name;
	this->tag = tag;
	this->layer = layer;
	this->sceneIndex = scene;
}

template<class T>
void GameObject::AddComponent()
{
	Project::componentManager->AddComponent(this, Project::ClassTypeToInt<T>());
}

template<class T>
T * GameObject::GetComponent()
{
	return Project::componentManager->GetComponent(this, Project::ClassTypeToInt<T>());
}

template<class T>
void GameObject::DeleteComponent()
{
	return Project::componentManager->DeleteComponent(this, Project::ClassTypeToInt<T>());
}

std::vector<GameObject> GameObject::FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex)
{
	// TO-DO
	return std::vector<GameObject>();
}
