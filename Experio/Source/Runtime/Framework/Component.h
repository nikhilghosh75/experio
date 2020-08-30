#pragma once

#include "stdint.h"
#include <vector>
#include "../Debug/Debug.h"

class GameObject;
class Scene;

class Component
{
protected:
	GameObject* gameObject;
	uint64_t id;
public:
	Component() {};
	Component(GameObject* object);
	Component(GameObject* object, uint64_t id);

	virtual void Start() {};

	virtual void Update() {};

	GameObject* GetGameObject() const { return gameObject; }
	uint64_t GetId() { return id; }

	friend Component* CopyComponent(GameObject* gameObject, Component* component, unsigned int classId);
};

class TestComponent : public Component
{
public:
	TestComponent(GameObject* object) { gameObject = object; Start(); };

	virtual void Start() override { Debug::Log("Started"); }

	virtual void Update() override { Debug::Log("Updating"); }
};