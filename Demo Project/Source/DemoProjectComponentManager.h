#pragma once
#include "Runtime/Framework/ComponentManager.h"
#include "Runtime/Debug/Debug.h"

#include "Runtime/Camera/CameraSystem.h"
#include "Runtime/Particles/ParticleSystem.h"
#include "Runtime/Rendering/Billboard.h"
#include "Runtime/Rendering/MeshComponent.h"
#include "Runtime/UI/TextComponent.h"

__declspec(dllexport) class DemoProjectComponentManager : public ComponentManager
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
		case 100:
			return CameraSystem::AddComponent(gameObject);
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
		case 100:
			return (Component*)CameraSystem::GetComponent(gameObject);
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

	virtual Component* GetComponentAtIndex(unsigned int classId, unsigned index) override
	{
		switch (classId)
		{
		case 2:
			PB_GET_COMPONENT_INDEX(testComponentInstances);
		case 100:
			Debug::Log("CameraSystem has not impleented GetComponentAtIndex"); return nullptr;
		case 101:
			PB_GET_COMPONENT_INDEX(meshInstances);
		case 102:
			PB_GET_COMPONENT_INDEX(particleSystemInstances);
		case 103:
			PB_GET_COMPONENT_INDEX(billboardInstances);
		case 104:
			PB_GET_COMPONENT_INDEX(textComponentInstances);
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
		case 100:
			CameraSystem::DeleteComponent(gameObject);
			break;
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

	virtual unsigned int ComponentCount() override
	{
		return testComponentInstances.size() + particleSystemInstances.size() + billboardInstances.size()
			+ meshInstances.size() + textComponentInstances.size();
	}
};