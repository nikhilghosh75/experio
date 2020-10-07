#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "../Math/FTransform.h"
#include "../Containers/TTypedTree.h"

class GameObject
{
public:
	unsigned short tag;
	uint8_t layer;
	uint8_t sceneIndex;
	std::string name;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	FVector3 localPosition;
	FQuaternion localRotation;
	FVector3 localScale;
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

	GameObject* AddChild(std::string name);

	// WORLD POSITION
	FVector3 GetPosition() const;
	FQuaternion GetRotation() const;
	FVector3 GetScale() const;

	void Translate(FVector3 translationAmount);
	void Rotate(FQuaternion rotationAmount);
	void Scale(float scaleFactor);

	void SetTransform(FVector3 position, FQuaternion rotation, FVector3 scale);

	static GameObject* FindObjectWithTag(std::string tag);
	static GameObject* FindObjectWithTag(unsigned short tag);

	static std::vector<GameObject*> FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex = 0);

	static unsigned int NumGameObjectsWithTag(unsigned short tag);

	template<typename T>
	static T* FindObjectOfType();

	template<typename T>
	static GameObject* FindGameObjectOfType();

	template<typename T>
	static T* GetComponentInChildren(GameObject* gameObject);

	template<typename T>
	static std::vector<T*> GetComponentsInChildren(GameObject* gameObject);

	static TTypedTree<GameObject>* MakeTree(GameObject* gameObject);
	static TTypedTree<GameObject>* MakeTree(uint8_t sceneIndex);

private:
	static void MakeSubtree(GameObject* gameObject, TTypedTreeNode<GameObject>* parent);
};

static void ForEach(GameObject* gameObject, std::function<void(GameObject*)> func);
