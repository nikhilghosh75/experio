#pragma once
#include <string>
#include <vector>
#include "Component.h"

class GameObject
{
public:
	unsigned short tag;
	uint8_t layer;
	uint8_t sceneIndex;
	std::vector<Component*> components;
	std::string* name;

	GameObject(std::string* name);
	GameObject(std::string* name, unsigned short tag, uint8_t layer);
	GameObject(std::string* name, unsigned short tag, uint8_t layer, uint8_t scene);

	template<class T>
	void AddComponent();

	template<class T>
	T* GetComponent();

	template<class T>
	void DeleteComponent();

	static std::vector<GameObject> FindGameObjectsWithTag(unsigned short tag, uint8_t sceneIndex = 0);
};
