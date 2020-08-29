#include "GameObject.h"
#include "Project.h"
#include "Scene.h"

GameObject::GameObject()
{
	this->name = (std::string)"";
	this->tag = 0;
	this->layer = 0;
	this->sceneIndex = 0;
}

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->tag = 0;
	this->layer = 0;
	this->sceneIndex = 0;
}

GameObject::GameObject(std::string name, unsigned short tag, uint8_t layer)
{
	this->name = name;
	this->tag = tag;
	this->layer = layer;
	this->sceneIndex = 0;
}

GameObject::GameObject(std::string name, unsigned short tag, uint8_t layer, uint8_t scene)
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

GameObject * GameObject::AddChild(std::string name)
{
	this->children.push_back(new GameObject(name));
	this->children[children.size() - 1]->parent = this;
	return children[children.size() - 1];
}

std::vector<GameObject> GameObject::FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex)
{
	// TO-DO
	return std::vector<GameObject>();
}

FVector3 GameObject::GetPosition() const
{
	GameObject* tempObject = this->parent;
	FVector3 position = localPosition;
	while (tempObject != nullptr)
	{
		position += tempObject->localPosition;
		tempObject = tempObject->parent;
	}
	return position;
}

FQuaternion GameObject::GetRotation() const
{
	GameObject* tempObject = this->parent;
	FQuaternion rotation = localRotation;
	while (tempObject != nullptr)
	{
		rotation *= tempObject->localRotation;
		tempObject = tempObject->parent;
	}
	return rotation;
}

FVector3 GameObject::GetScale() const
{
	GameObject* tempObject = this->parent;
	FVector3 scale = localScale;
	while (tempObject != nullptr)
	{
		scale *= tempObject->localScale;
		tempObject = tempObject->parent;
	}
	return scale;
}

void GameObject::Translate(FVector3 translationAmount)
{
	this->localPosition += translationAmount;
}

void GameObject::Rotate(FQuaternion rotationAmount)
{
	this->localRotation *= rotationAmount;
}

void GameObject::Scale(float scaleFactor)
{
	this->localScale *= scaleFactor;
}

void GameObject::SetTransform(FVector3 position, FQuaternion rotation, FVector3 scale)
{
	this->localPosition = position;
	this->localRotation = rotation;
	this->localScale = scale;
}

GameObject * GameObject::FindObjectWithTag(std::string tag)
{
	/*
	unsigned short tagID = Project::TagStringToNum(tag.c_str());
	for (int i = 0; i < MAX_SCENES; i++)
	{
		Scene* currentScene = &Scene::scenes[i];
		if (!currentScene->isActive)
		{
			continue;
		}
		GameObject* hierarchy = currentScene->sceneRoot;
		TTypedTreeIterator<GameObject> iterator(hierarchy);
		while (!iterator.IsAtEnd())
		{
			if (iterator.current->object.tag == tagID)
			{
				return &iterator.current->object;
			}
			iterator.Increment();
		}
	}
	return nullptr;
	*/
	return nullptr;
}

GameObject * GameObject::FindObjectWithTag(unsigned short tag)
{
	/*
	for (int i = 0; i < MAX_SCENES; i++)
	{
		Scene* currentScene = &Scene::scenes[i];
		if (!currentScene->isActive)
		{
			continue;
		}
		TTypedTree<GameObject>* hierarchy = &currentScene->sceneHiearchy;
		TTypedTreeIterator<GameObject> iterator(hierarchy);
		while (!iterator.IsAtEnd())
		{
			if (iterator.current->object.tag == tag)
			{
				return &iterator.current->object;
			}
			iterator.Increment();
		}
	}
	return nullptr;
	*/
	return nullptr;
}