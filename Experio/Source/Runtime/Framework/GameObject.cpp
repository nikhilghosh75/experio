#include "GameObject.h"
#include "Project.h"
#include "Scene.h"
#include "GameObjectIterator.h"

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

template<typename T>
T * GameObject::FindObjectOfType()
{
	return (T*)Project::componentManager->GetComponentAtIndex(Project::ClassTypeToInt<T>(), 0);
}

template<typename T>
GameObject * GameObject::FindGameObjectOfType()
{
	return Project::componentManager->GetComponentAtIndex(Project::ClassTypeToInt<T>(), 0)->GetGameObject();
}

template<typename T>
T * GameObject::GetComponentInChildren(GameObject * gameObject)
{
	T* foundObject = Project::componentManager->GetComponent(gameObject, Project::ClassTypeToInt<T>());
	if (foundObject != nullptr)
	{
		return foundObject;
	}

	for (int i = 0; i < gameObject->children.size(); i++)
	{
		foundObject = GetComponentInChildren(gameObject->children[i]);
		if (foundObject)
		{
			return foundObject;
		}
	}

	return nullptr;
}

template<typename T>
std::vector<T*> GameObject::GetComponentsInChildren(GameObject * gameObject)
{
	std::vector<T*> components;
	T* foundObject = Project::componentManager->GetComponent(gameObject, Project::ClassTypeToInt<T>());
	if (foundObject != nullptr)
	{
		components.push_back(foundObject);
	}

	GameObjectIterator iterator(gameObject);
	while (!iterator.IsAtEnd())
	{
		T* foundObject = Project::componentManager->GetComponent(iterator.current, Project::ClassTypeToInt<T>());
		if (foundObject != nullptr)
		{
			components.push_back(foundObject);
		}
		iterator.Increment();
	}
	return components;
}

GameObject * GameObject::AddChild(std::string name)
{
	this->children.push_back(new GameObject(name));
	this->children[children.size() - 1]->parent = this;
	return children[children.size() - 1];
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
	unsigned short tagID = Project::TagStringToNum(tag.c_str());
	for (int i = 0; i < MAX_SCENES; i++)
	{
		Scene* currentScene = &Scene::scenes[i];
		if (!currentScene->isActive)
		{
			continue;
		}
		GameObject* root = &currentScene->sceneRoot;
		GameObjectIterator iterator(root);
		while (!iterator.IsAtEnd())
		{
			if (iterator.current->tag == tagID)
			{
				return iterator.current;
			}
			iterator.Increment();
		}
	}
	return nullptr;
}

GameObject * GameObject::FindObjectWithTag(unsigned short tag)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		Scene* currentScene = &Scene::scenes[i];
		if (!currentScene->isActive)
		{
			continue;
		}
		GameObject* root = &currentScene->sceneRoot;
		GameObjectIterator iterator(root);
		while (!iterator.IsAtEnd())
		{
			if (iterator.current->tag == tag)
			{
				return iterator.current;
			}
			iterator.Increment();
		}
	}
	return nullptr;
}

std::vector<GameObject*> GameObject::FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex)
{
	std::vector<GameObject*> objects;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		Scene* currentScene = &Scene::scenes[i];
		if (!currentScene->isActive)
		{
			continue;
		}
		GameObject* root = &currentScene->sceneRoot;
		GameObjectIterator iterator(root);
		while (!iterator.IsAtEnd())
		{
			if (iterator.current->tag == tag)
			{
				objects.push_back(iterator.current);
			}
			iterator.Increment();
		}
	}
	return objects;
}

unsigned int GameObject::NumGameObjectsWithTag(unsigned short tag)
{
	int num = 0;
	for (int i = 0; i < MAX_SCENES; i++)
	{
		Scene* currentScene = &Scene::scenes[i];
		if (!currentScene->isActive)
		{
			continue;
		}
		GameObject* root = &currentScene->sceneRoot;
		GameObjectIterator iterator(root);
		while (!iterator.IsAtEnd())
		{
			if (iterator.current->tag == tag)
			{
				num++;
			}
			iterator.Increment();
		}
	}

	return num;
}

TTypedTree<GameObject>* GameObject::MakeTree(GameObject * gameObject)
{
	TTypedTree<GameObject>* objectTree = new TTypedTree<GameObject>(*gameObject);
	
	for (int i = 0; i < gameObject->children.size(); i++)
	{
		MakeSubtree(gameObject->children[i], objectTree->GetRoot());
	}

	return objectTree;
}

TTypedTree<GameObject>* GameObject::MakeTree(uint8_t sceneIndex)
{
	return MakeTree(&Scene::scenes[sceneIndex].sceneRoot);
}

void GameObject::MakeSubtree(GameObject * gameObject, TTypedTreeNode<GameObject>* parent)
{
	TTypedTreeNode<GameObject> current = parent->AddChild(*gameObject);
	
	for (int i = 0; i < gameObject->children.size(); i++)
	{
		MakeSubtree(gameObject->children[i], &current);
	}
}

void ForEach(GameObject * gameObject, std::function<void(GameObject*)> func)
{
	func(gameObject);

	for (int i = 0; i < gameObject->children.size(); i++)
	{
		ForEach(gameObject->children[i], func);
	}
}
