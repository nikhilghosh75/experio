#include "GameObject.h"
#include "Project.h"
#include "Scene.h"
#include "GameObjectIterator.h"
#include "glm/gtx/matrix_decompose.hpp"
#include "../Containers/Algorithm.h"
#include "../Core/Window.h"
#include "../UI/Canvas.h"

uint64_t GameObject::currentGameObject = 64;

#define PB_ASSIGN_DEFAULT_ID() this->id = currentGameObject; currentGameObject++;

GameObject::GameObject()
{
	this->name = (std::string)"";
	this->tag = 0;
	this->layer = 0;
	this->sceneIndex = 0;
	this->isUI = false;

	this->localPosition = FVector3(0, 0, 0);
	this->localRotation = FQuaternion(0, 0, 0, 1);
	this->localScale = FVector3(1, 1, 1);

	PB_ASSIGN_DEFAULT_ID()
}

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->tag = 0;
	this->layer = 0;
	this->sceneIndex = 0;
	this->isUI = false;

	this->localPosition = FVector3(0, 0, 0);
	this->localRotation = FQuaternion(0, 0, 0, 1);
	this->localScale = FVector3(1, 1, 1);

	PB_ASSIGN_DEFAULT_ID()
}

GameObject::GameObject(std::string name, unsigned short tag, uint8_t layer)
{
	this->name = name;
	this->tag = tag;
	this->layer = layer;
	this->sceneIndex = 0;
	this->isUI = false;

	this->localPosition = FVector3(0, 0, 0);
	this->localRotation = FQuaternion(0, 0, 0, 1);
	this->localScale = FVector3(1, 1, 1);

	PB_ASSIGN_DEFAULT_ID()
}

GameObject::GameObject(std::string name, unsigned short tag, uint8_t layer, uint8_t scene)
{
	this->name = name;
	this->tag = tag;
	this->layer = layer;
	this->sceneIndex = scene;
	this->isUI = false;

	this->localPosition = FVector3(0, 0, 0);
	this->localRotation = FQuaternion(0, 0, 0, 1);
	this->localScale = FVector3(1, 1, 1);

	PB_ASSIGN_DEFAULT_ID()
}

GameObject::~GameObject()
{
	if (Project::componentManager != nullptr && Project::projectRunning) { Project::componentManager->OnGameObjectDeleted(this); }
}

void GameObject::AddComponentByComponentID(unsigned int id)
{
	Project::componentManager->AddComponent(this, id);
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
	Project::componentManager->DeleteComponent(this, Project::ClassTypeToInt<T>());
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

void GameObject::DeleteComponentByComponentID(unsigned int id)
{
	Project::componentManager->DeleteComponent(this, id);
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

void GameObject::SetTransform(FTransform transform)
{
	this->localPosition = transform.GetPosition();
	this->localRotation = transform.GetRotation();
	this->localScale = transform.GetScale();
}

void GameObject::SetTransform(FVector3 position, FQuaternion rotation, FVector3 scale)
{
	this->localPosition = position;
	this->localRotation = rotation;
	this->localScale = scale;
}

void GameObject::SetTransform(glm::mat4 localMatrix)
{
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(localMatrix, scale, rotation, translation, skew, perspective);

	glm::quat correctRotation = glm::conjugate(rotation); // glm::decompose returns conjugate
	this->localPosition = (FVector3)translation;
	this->localRotation = (FQuaternion)correctRotation;
	this->localScale = (FVector3)scale;
}

FRect GameObject::GetCanvasSpaceRect() const
{
	if (!isUI)
	{
		// return FRect();
	}

	float canvasWidth = Canvas::GetCanvasWidth();
	float canvasHeight = Canvas::GetCanvasHeight();

	float xPosition = 0;
	float yPosition = 0;
	float width = canvasWidth;
	float height = canvasHeight;

	std::vector<size_t> siblingIndexes;

	const GameObject* current = this;
	while (current != nullptr)
	{
		if (!current->isUI || current->parent == nullptr)
			break;

		siblingIndexes.push_back(current->GetSiblingIndex());

		if (current->parent->isUI)
		{
			xPosition = MergePositionConstraint(xPosition, current->rectTransform.xConstraint);
			yPosition = MergePositionConstraint(yPosition, current->rectTransform.yConstraint);
		}
		else
		{
			if (xPosition < 0)
				xPosition = canvasWidth - xPosition;
			if (yPosition < 0)
				yPosition = canvasHeight - yPosition;
		}

		current = current->parent;
	}

	size_t objectDepth = siblingIndexes.size();
	for (size_t i = 0; i < objectDepth; i++)
	{
		width = MergeDimensionConstraint(width, current->rectTransform.widthConstraint);
		height = MergeDimensionConstraint(height, current->rectTransform.heightConstraint);

		current = current->children[siblingIndexes.back()];
		siblingIndexes.pop_back();
	}

	return FRect(xPosition, yPosition, xPosition + width, xPosition + height);
}

void GameObject::SetTag(unsigned short newTag)
{
	this->tag = newTag;
}

void GameObject::SetTag(const std::string& newTag)
{
	this->tag = Project::TagStringToNum(newTag.c_str());
}

void GameObject::EmptyChildren()
{
	this->children.clear();
}

void GameObject::ReserveChildren(uint8_t numChildren)
{
	this->children.reserve(numChildren);
}

Scene * GameObject::GetScene() const
{
	return &Scene::scenes[this->sceneIndex];
}

size_t GameObject::GetSiblingIndex() const
{
	if (parent == nullptr)
		return 0;

	for (size_t i = 0; i < parent->children.size(); i++)
	{
		if (parent->children[i] == this)
			return i;
	}

	return parent->children.size();
}

bool GameObject::operator==(const GameObject & object) const
{
	return (name == object.name) && (this->layer == object.layer)
		&& (this->tag == object.tag) && (sceneIndex == object.sceneIndex);
}

bool GameObject::operator!=(const GameObject & object) const
{
	return (name != object.name) || (this->layer != object.layer)
		|| (this->tag != object.tag) || (sceneIndex != object.sceneIndex);
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

void GameObject::Reparent(GameObject* newParent, GameObject* newChild)
{
	newParent->children.push_back(newChild);

	if (newChild->parent != nullptr)
	{
		Experio::Algorithm::RemoveElement(newChild->parent->children, newChild);
	}

	newChild->parent = newParent;
}

GameObject * GameObject::FindGameObjectOfID(uint64_t id)
{
	for (int i = 0; i < MAX_SCENES; i++)
	{
		GameObject* foundObject = FindGameObjectOfID(id, i);
		if (foundObject != nullptr)
		{
			return foundObject;
		}
	}
	return nullptr;
}

GameObject * GameObject::FindGameObjectOfID(uint64_t id, uint8_t sceneIndex)
{
	Scene* currentScene = &Scene::scenes[sceneIndex];
	if (!currentScene->isActive)
	{
		return nullptr;
	}
	GameObject* root = &currentScene->sceneRoot;
	GameObjectIterator iterator(root);
	while (!iterator.IsAtEnd())
	{
		if (iterator.current->id == id)
		{
			return iterator.current;
		}
		iterator.Increment();
	}
	return nullptr;
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
