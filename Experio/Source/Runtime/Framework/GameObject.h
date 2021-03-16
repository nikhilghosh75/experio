#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "../Math/FTransform.h"
#include "../UI/RectTransform.h"
#include "../Containers/TTypedTree.h"

/// <summary>
/// An object existing in the scene. Generally contain components
/// </summary>

class GameObject
{
	static uint64_t currentGameObject;
public:
	unsigned short tag;
	uint8_t layer;
	uint8_t sceneIndex;
	std::string name;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	
	// Meant so that the RectTransform and regular transform can exist at the same time
	union
	{
		struct
		{
			FVector3 localPosition;
			FQuaternion localRotation;
			FVector3 localScale;
		};
		struct
		{
			RectTransform rectTransform;
		};
	};

	uint64_t id;
	bool isActive = true;
	bool isUI;

	GameObject();
	GameObject(std::string name);
	GameObject(std::string name, unsigned short tag, uint8_t layer);
	GameObject(std::string name, unsigned short tag, uint8_t layer, uint8_t scene);

	~GameObject();

	template<class T>
	void AddComponent();

	void AddComponentByComponentID(unsigned int id);

	template<class T>
	T* GetComponent();

	template<class T>
	void DeleteComponent();

	void DeleteComponentByComponentID(unsigned int id);

	GameObject* AddChild(std::string name);

	// Meant for non-UI gameObject
	// WORLD POSITION/ROTATION/SCALE
	FVector3 GetPosition() const;
	FQuaternion GetRotation() const;
	FVector3 GetScale() const;

	void Translate(FVector3 translationAmount);
	void Rotate(FQuaternion rotationAmount);
	void Scale(float scaleFactor);

	void SetTransform(FTransform transform);
	void SetTransform(FVector3 position, FQuaternion rotation, FVector3 scale);
	void SetTransform(glm::mat4 localMatrix);

	// Meant for UI game objects
	FRect GetCanvasSpaceRect() const;

	void SetTag(unsigned short newTag);
	void SetTag(const std::string& newTag);

	void EmptyChildren();

	void ReserveChildren(uint8_t numChildren);

	Scene* GetScene() const;

	bool operator==(const GameObject& object) const;
	bool operator!=(const GameObject& object) const;

	static GameObject* FindObjectWithTag(std::string tag);
	static GameObject* FindObjectWithTag(unsigned short tag);

	static std::vector<GameObject*> FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex = 0);

	static unsigned int NumGameObjectsWithTag(unsigned short tag);

	static void Reparent(GameObject* newParent, GameObject* newChild);

	static GameObject* FindGameObjectOfID(uint64_t id);
	static GameObject* FindGameObjectOfID(uint64_t id, uint8_t sceneIndex);

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

void ForEach(GameObject* gameObject, std::function<void(GameObject*)> func);