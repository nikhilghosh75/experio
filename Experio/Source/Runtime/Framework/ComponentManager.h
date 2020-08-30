#pragma once
#include "Component.h"
#include "Scene.h"
#include "../Debug/Debug.h"
#include "../Particles/ParticleSystem.h"
#include "../Rendering/Billboard.h"
#include "../Rendering/MeshComponent.h"
#include "../UI/TextComponent.h"
#include "../Camera/CameraSystem.h"

class ComponentManager
{
public:
	virtual void Update() {};

	virtual Component* AddComponent(GameObject* gameObject, unsigned int id) { return nullptr; };

	virtual Component* GetComponent(GameObject* gameObject, unsigned int classId) { return nullptr; };

	virtual void DeleteComponent(GameObject* gameObject, unsigned int classId) {};

	virtual std::vector<unsigned int> GetComponentsIDsInGameObject(GameObject* gameObject) { return std::vector<unsigned int>(); };
	virtual std::vector<Component*> GetComponentsInGameObject(GameObject* gameObject) { return std::vector<Component*>(); };
};

#define PB_ADD_COMPONENT(_vectorName_) _vectorName_.emplace_back(gameObject); return (Component*)(&_vectorName_[_vectorName_.size() - 1]);

#define PB_GET_COMPONENT(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(_vectorName_[i].GetGameObject() == gameObject)\
		{\
			return (Component*)(&(_vectorName_[i]));\
		}\
	}\
	return nullptr;

#define PB_DELETE_COMPONENT(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(gameObject == _vectorName_[i].GetGameObject())\
		{\
			foundComponent = true;\
		}\
		if(foundComponent)\
		{\
			if (i + 1 == _vectorName_.size())\
			{\
				_vectorName_.pop_back();\
				return;\
			}\
			_vectorName_[i] = _vectorName_[i + 1];\
		}\
	}\
	break;\

#define PB_UPDATE(_vectorName_) for(int i = 0; i < _vectorName_.size(); i++)\
	{\
		if(!Scene::IsActive(_vectorName_[i].GetGameObject())) { continue; }\
		_vectorName_[i].Update();\
	}\

class TestComponentManager : public ComponentManager
{
	const std::vector<unsigned int> classIds = { 2, 100, 101, 102, 103, 104 };
public:
	std::vector<TestComponent> testComponentInstances;
	std::vector<ParticleSystem> particleSystemInstances;
	std::vector<Billboard> billboardInstances;
	std::vector<MeshComponent> meshInstances;
	std::vector<TextComponent> textComponentInstances;

	virtual void Update() override 
	{
		CameraSystem::Update();
		PB_UPDATE(testComponentInstances);
		PB_UPDATE(meshInstances);
		PB_UPDATE(particleSystemInstances);
		PB_UPDATE(billboardInstances);
	}

	virtual Component* AddComponent(GameObject* gameObject, unsigned int classId) override
	{
		switch (classId)
		{
		case 2:
			PB_ADD_COMPONENT(testComponentInstances);
		case 101:
			PB_ADD_COMPONENT(meshInstances);
		case 102:
			PB_ADD_COMPONENT(particleSystemInstances);
		case 103:
			PB_ADD_COMPONENT(billboardInstances);
		case 104:
			PB_ADD_COMPONENT(textComponentInstances);
		default:
			Debug::LogError("Component cannot be found. Make sure to regenerate the project");
			return nullptr;
		}
	}

	virtual Component* GetComponent(GameObject* gameObject, unsigned int classId) override
	{
		switch (classId)
		{
		case 2:
			PB_GET_COMPONENT(testComponentInstances);
		case 101:
			PB_GET_COMPONENT(meshInstances);
		case 102:
			PB_GET_COMPONENT(particleSystemInstances);
		case 103:
			PB_GET_COMPONENT(billboardInstances);
		case 104:
			PB_GET_COMPONENT(textComponentInstances);
		}

		Debug::LogError("Component cannot be found. Make sure to regenerate the project");
		return nullptr;
	}

	virtual void DeleteComponent(GameObject* gameObject, unsigned int classId) override
	{
		bool foundComponent = false;
		switch (classId)
		{
		case 2:
			PB_DELETE_COMPONENT(testComponentInstances);
		case 101:
			PB_DELETE_COMPONENT(meshInstances);
		case 102:
			PB_DELETE_COMPONENT(particleSystemInstances);
		case 103:
			PB_DELETE_COMPONENT(billboardInstances);
		case 104:
			PB_DELETE_COMPONENT(textComponentInstances);
		}
	}

	virtual std::vector<unsigned int> GetComponentIDsInGameObject(GameObject* gameObject)
	{
		std::vector<unsigned int> returnVector;
		for (int i = 0; i < classIds.size(); i++)
		{
			if (GetComponent(gameObject, classIds[i]) != nullptr)
			{
				returnVector.push_back(classIds[i]);
			}
		}
		
		return returnVector;
	}

	virtual std::vector<Component*> GetComponentsInGameObject(GameObject* gameObject)
	{
		std::vector<Component*> returnVector;
		for (int i = 0; i < classIds.size(); i++)
		{
			Component* component = GetComponent(gameObject, classIds[i]);
			if (component != nullptr)
			{
				returnVector.push_back(component);
			}
		}

		return returnVector;
	}
};