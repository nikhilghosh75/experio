#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "../Math/FTransform.h"
#include "../Containers/TTypedTree.h"

class GameObject
{
public:
	// FVector3 localPosition;
	// FQuaternion localRotation;
	// FVector3 localScale;

	unsigned short tag;
	uint8_t layer;
	uint8_t sceneIndex;
	std::string name;
	FTransform transform;
	bool isActive = true;

	GameObject();
	GameObject(std::string name);
	GameObject(std::string name, unsigned short tag, uint8_t layer);
	GameObject(std::string name, unsigned short tag, uint8_t layer, uint8_t scene);

	template<class T>
	void AddComponent();

	template<class T>
	T* GetComponent();

	template<class T>
	void DeleteComponent();

	static std::vector<GameObject> FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex = 0);

	FVector3 GetPosition() const;
	FQuaternion GetRotation() const;
	FVector3 GetScale() const;

	void SetPosition(FVector3 newPosition);
	void SetPosition(float x, float y, float z);
	void SetRotation(FQuaternion newRotation);
	void SetRotation(float x, float y, float z, float w);
	void SetScale(FVector3 newScale);
	void SetScale(float x, float y, float z);

	void Translate(FVector3 translationAmount);
	void Rotate(FQuaternion rotationAmount);
	void Scale(float scaleFactor);

	static GameObject* FindObjectWithTag(std::string tag);
	static GameObject* FindObjectWithTag(unsigned short tag);
};
