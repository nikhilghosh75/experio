#pragma once

#include "stdint.h"
#include <vector>
#include "../Debug/GDebug.h"

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

	GameObject* GetGameObject() { return gameObject; }
	uint64_t GetId() { return id; }
};

class TestComponent : public Component
{
public:
	TestComponent(GameObject* object) { gameObject = object; };

	virtual void Start() override { GDebug::Log("Started"); }

	virtual void Update() override { GDebug::Log("Updating"); }
};