#include "DemoProjectComponentManager.h"
#include "Runtime/Debug/Debug.h"

void DemoProjectComponentManager::Start()
{
	PB_START(testComponentInstances);
	PB_START(meshInstances);
	PB_START(particleSystemInstances);
	PB_START(billboardInstances);
}

void DemoProjectComponentManager::Update()
{
	CameraSystem::Update();
	PB_UPDATE(testComponentInstances);
	PB_UPDATE(meshInstances);
	PB_UPDATE(particleSystemInstances);
	PB_UPDATE(billboardInstances);
}

void DemoProjectComponentManager::RenderScene()
{
	CameraSystem::Update();
	PB_UPDATE(meshInstances);
	PB_UPDATE(billboardInstances);
	PB_UPDATE(particleSystemInstances);
}

Component * DemoProjectComponentManager::AddComponent(GameObject * gameObject, unsigned int classId)
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

Component * DemoProjectComponentManager::GetComponent(GameObject * gameObject, unsigned int classId)
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

Component * DemoProjectComponentManager::GetComponentAtIndex(unsigned int classId, unsigned index)
{
	switch (classId)
	{
	case 2:
		PB_GET_COMPONENT_INDEX(testComponentInstances);
	case 100:
		Debug::Log("CameraSystem has not implemented GetComponentAtIndex"); return nullptr;
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

void DemoProjectComponentManager::DeleteComponent(GameObject * gameObject, unsigned int classId)
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

void DemoProjectComponentManager::OnGameObjectDeleted(GameObject * gameObject)
{
	bool foundComponent = false;

	PB_DELETE_COMPONENT(testComponentInstances); foundComponent = false;
	CameraSystem::OnGameObjectDeleted(gameObject);
	PB_DELETE_COMPONENT(meshInstances); foundComponent = false;
	PB_DELETE_COMPONENT(particleSystemInstances); foundComponent = false;
	PB_DELETE_COMPONENT(billboardInstances); foundComponent = false;
	PB_DELETE_COMPONENT(textComponentInstances); foundComponent = false;
}

std::vector<unsigned int> DemoProjectComponentManager::GetComponentsIDsInGameObject(GameObject * gameObject)
{
	std::vector<unsigned int> returnVector;

	PB_GET_COMPONENT_IDS(2);
	PB_GET_COMPONENT_IDS(100);
	PB_GET_COMPONENT_IDS(101);
	PB_GET_COMPONENT_IDS(102);
	PB_GET_COMPONENT_IDS(103);
	PB_GET_COMPONENT_IDS(104);

	return returnVector;
}

std::vector<Component*> DemoProjectComponentManager::GetComponentsInGameObject(GameObject * gameObject)
{
	std::vector<Component*> returnVector;
	Component* component;

	PB_GET_COMPONENT_GAMEOBJECT(2);
	PB_GET_COMPONENT_GAMEOBJECT(100);
	PB_GET_COMPONENT_GAMEOBJECT(101);
	PB_GET_COMPONENT_GAMEOBJECT(102);
	PB_GET_COMPONENT_GAMEOBJECT(103);
	PB_GET_COMPONENT_GAMEOBJECT(104);

	return returnVector;
}

std::vector<Component*> DemoProjectComponentManager::GetAllComponents()
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

void DemoProjectComponentManager::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds)
{
	components.reserve(ComponentCount());
	componentIds.reserve(ComponentCount());

	PB_GET_ALL_IDS(testComponentInstances, 2);
	PB_GET_ALL_IDS(meshInstances, 101);
	PB_GET_ALL_IDS(particleSystemInstances, 102);
	PB_GET_ALL_IDS(billboardInstances, 103);
	PB_GET_ALL_IDS(textComponentInstances, 104);
}

void DemoProjectComponentManager::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds, uint8_t sceneIndex)
{
	components.reserve(ComponentCount());
	componentIds.reserve(ComponentCount());

	PB_GET_ALL_SCENE_IDS(testComponentInstances, 2);
	PB_GET_ALL_SCENE_IDS(meshInstances, 101);
	PB_GET_ALL_SCENE_IDS(particleSystemInstances, 102);
	PB_GET_ALL_SCENE_IDS(billboardInstances, 103);
	PB_GET_ALL_SCENE_IDS(textComponentInstances, 104);
}

unsigned int DemoProjectComponentManager::ComponentCount() const
{
	return CameraSystem::Size() + testComponentInstances.size() + particleSystemInstances.size()
		+ billboardInstances.size() + meshInstances.size()
		+ textComponentInstances.size();
}
