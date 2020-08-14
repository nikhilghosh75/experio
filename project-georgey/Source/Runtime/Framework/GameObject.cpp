#include "GameObject.h"
#include "Project.h"

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

std::vector<GameObject> GameObject::FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex)
{
	// TO-DO
	return std::vector<GameObject>();
}

FVector3 GameObject::GetPosition() const
{
	return transform.GetPosition();
}

FQuaternion GameObject::GetRotation() const
{
	return transform.GetRotation();
}

FVector3 GameObject::GetScale() const
{
	return transform.GetScale();
}

void GameObject::SetPosition(FVector3 newPosition)
{
	this->transform.SetPosition(newPosition);
}

void GameObject::SetPosition(float x, float y, float z)
{
	this->transform.SetPosition(FVector3(x, y, z));
}

void GameObject::SetRotation(FQuaternion newRotation)
{
	this->transform.SetRotation(newRotation);
}

void GameObject::SetRotation(float x, float y, float z, float w)
{
	this->transform.SetRotation(FQuaternion(x, y, z, w));
}

void GameObject::SetScale(FVector3 newScale)
{
	this->transform.SetScale(newScale);
}

void GameObject::SetScale(float x, float y, float z)
{
	this->transform.SetScale(FVector3(x, y, z));
}

void GameObject::Translate(FVector3 translationAmount)
{
	this->transform.Translate(translationAmount);
}

void GameObject::Rotate(FQuaternion rotationAmount)
{
	this->transform.Rotate(rotationAmount);
}

void GameObject::Scale(float scaleFactor)
{
	this->transform.Scale(scaleFactor);
}
