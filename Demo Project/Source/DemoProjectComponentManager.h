#pragma once
#include "Runtime/Framework/ComponentManager.h"
#include "Runtime/Debug/Debug.h"

#include "Runtime/Camera/CameraSystem.h"
#include "Runtime/Rendering/Particles/ParticleSystem.h"
#include "Runtime/Rendering/Components/Billboard.h"
#include "Runtime/Rendering/Components/MeshComponent.h"
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

	virtual void Start() override
	{
		PB_START(testComponentInstances);
		PB_START(meshInstances);
		PB_START(particleSystemInstances);
		PB_START(billboardInstances);
	}

	virtual void Update() override
	{
		CameraSystem::Update();
		PB_UPDATE(testComponentInstances);
		PB_UPDATE(meshInstances);
		PB_UPDATE(particleSystemInstances);
		PB_UPDATE(billboardInstances);
	}

	virtual void RenderScene() override
	{
		CameraSystem::Update();
		PB_UPDATE(meshInstances);
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
			PB_DELETE_COMPONENT(testComponentInstances); break;
		case 100:
			CameraSystem::DeleteComponent(gameObject);
			break;
		case 101:
			PB_DELETE_COMPONENT(meshInstances); break;
		case 102:
			PB_DELETE_COMPONENT(particleSystemInstances); break;
		case 103:
			PB_DELETE_COMPONENT(billboardInstances); break;
		case 104:
			PB_DELETE_COMPONENT(textComponentInstances); break;
		}
	}

	virtual void OnGameObjectDeleted(GameObject* gameObject) override
	{
		bool foundComponent = false;

		PB_DELETE_COMPONENT(testComponentInstances); foundComponent = false;
		CameraSystem::OnGameObjectDeleted(gameObject);
		PB_DELETE_COMPONENT(meshInstances); foundComponent = false;
		PB_DELETE_COMPONENT(particleSystemInstances); foundComponent = false;
		PB_DELETE_COMPONENT(billboardInstances); foundComponent = false;
		PB_DELETE_COMPONENT(textComponentInstances); foundComponent = false;
	}

	virtual std::vector<unsigned int> GetComponentsIDsInGameObject(GameObject* gameObject) override
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

	virtual std::vector<Component*> GetComponentsInGameObject(GameObject* gameObject) override
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

	virtual std::vector<Component*> GetAllComponents() override
	{
		std::vector<Component*> vector;
		vector.reserve(ComponentCount());

		PB_GET_ALL(testComponentInstances);
		PB_GET_ALL(particleSystemInstances);
		PB_GET_ALL(billboardInstances);
		PB_GET_ALL(meshInstances);
		PB_GET_ALL(textComponentInstances);
		
		return vector;
	}

	virtual void GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds) override
	{
		components.reserve(ComponentCount());
		componentIds.reserve(ComponentCount());

		PB_GET_ALL_IDS(testComponentInstances, 2);
		PB_GET_ALL_IDS(meshInstances, 101);
		PB_GET_ALL_IDS(particleSystemInstances, 102);
		PB_GET_ALL_IDS(billboardInstances, 103);
		PB_GET_ALL_IDS(textComponentInstances, 104);
	}

	virtual void GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds, uint8_t sceneIndex)
	{
		components.reserve(ComponentCount());
		componentIds.reserve(ComponentCount());

		PB_GET_ALL_SCENE_IDS(testComponentInstances, 2);
		PB_GET_ALL_SCENE_IDS(meshInstances, 101);
		PB_GET_ALL_SCENE_IDS(particleSystemInstances, 102);
		PB_GET_ALL_SCENE_IDS(billboardInstances, 103);
		PB_GET_ALL_SCENE_IDS(textComponentInstances, 104);
	}

	virtual unsigned int ComponentCount() const override
	{
		return testComponentInstances.size() + particleSystemInstances.size() 
			+ billboardInstances.size() + meshInstances.size() 
			+ textComponentInstances.size();
	}
};