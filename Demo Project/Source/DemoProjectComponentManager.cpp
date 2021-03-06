#include "DemoProjectComponentManager.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Debug/Debug.h"

void DemoProjectComponentManager::Start()
{
	cameraSystem.Start();
	PB_START(textComponentInstances);
	PB_START(spaceshipInstances);
	PB_START(meshComponentInstances);
	PB_START(particleSystemInstances);
	PB_START(billboardInstances);
}

void DemoProjectComponentManager::Update()
{
	cameraSystem.Update();
	PB_UPDATE(textComponentInstances);
	PB_UPDATE(spaceshipInstances);
	PB_UPDATE(meshComponentInstances);
	PB_UPDATE(particleSystemInstances);
	PB_UPDATE(billboardInstances);
}

void DemoProjectComponentManager::RenderScene()
{
	cameraSystem.Update();
	PB_UPDATE(meshComponentInstances);
	PB_UPDATE(particleSystemInstances);
	PB_UPDATE(billboardInstances);
}

Component* DemoProjectComponentManager::AddComponent(GameObject* gameObject, unsigned int classId)
{
	switch(classId)
	{
		case 100: return cameraSystem.AddComponent(gameObject);
		case 104: PB_ADD_COMPONENT(textComponentInstances);
		case 1024: PB_ADD_COMPONENT(spaceshipInstances);
		case 101: PB_ADD_COMPONENT(meshComponentInstances);
		case 102: PB_ADD_COMPONENT(particleSystemInstances);
		case 103: PB_ADD_COMPONENT(billboardInstances);
	}
}

Component* DemoProjectComponentManager::GetComponent(GameObject* gameObject, unsigned int classId)
{
	switch(classId)
	{
		case 100: return cameraSystem.GetComponent(gameObject);
		case 104: PB_GET_COMPONENT(textComponentInstances);
		case 1024: PB_GET_COMPONENT(spaceshipInstances);
		case 101: PB_GET_COMPONENT(meshComponentInstances);
		case 102: PB_GET_COMPONENT(particleSystemInstances);
		case 103: PB_GET_COMPONENT(billboardInstances);
	}
}

void DemoProjectComponentManager::DeleteComponent(GameObject* gameObject, unsigned int classId)
{
	bool foundComponent = false;

	switch(classId)
	{
		case 100: return cameraSystem.DeleteComponent(gameObject);
		case 104: PB_DELETE_COMPONENT(textComponentInstances);
		case 1024: PB_DELETE_COMPONENT(spaceshipInstances);
		case 101: PB_DELETE_COMPONENT(meshComponentInstances);
		case 102: PB_DELETE_COMPONENT(particleSystemInstances);
		case 103: PB_DELETE_COMPONENT(billboardInstances);
	}
}

Component* DemoProjectComponentManager::GetComponentAtIndex(unsigned int classId, unsigned int index)
{
	switch(classId)
	{
		case 100: Debug::Log("CameraSystem has not implemented GetComponentAtIndex"); return nullptr;
		case 104: PB_GET_COMPONENT_INDEX(textComponentInstances);
		case 1024: PB_GET_COMPONENT_INDEX(spaceshipInstances);
		case 101: PB_GET_COMPONENT_INDEX(meshComponentInstances);
		case 102: PB_GET_COMPONENT_INDEX(particleSystemInstances);
		case 103: PB_GET_COMPONENT_INDEX(billboardInstances);
	}
}

void DemoProjectComponentManager::OnGameObjectDeleted(GameObject* gameObject)
{
	bool foundComponent = false;

	cameraSystem.OnGameObjectDeleted(gameObject);
	PB_DELETE_COMPONENT(textComponentInstances); foundComponent = false;
	PB_DELETE_COMPONENT(spaceshipInstances); foundComponent = false;
	PB_DELETE_COMPONENT(meshComponentInstances); foundComponent = false;
	PB_DELETE_COMPONENT(particleSystemInstances); foundComponent = false;
	PB_DELETE_COMPONENT(billboardInstances); foundComponent = false;
}

std::vector<Component*> DemoProjectComponentManager::GetComponentsInGameObject(GameObject * gameObject)
{
	std::vector<Component*> returnVector;
	Component* component;
	returnVector.reserve(ComponentCount());

	PB_GET_COMPONENT_GAMEOBJECT(104);
	PB_GET_COMPONENT_GAMEOBJECT(1024);
	PB_GET_COMPONENT_GAMEOBJECT(100);
	PB_GET_COMPONENT_GAMEOBJECT(101);
	PB_GET_COMPONENT_GAMEOBJECT(102);
	PB_GET_COMPONENT_GAMEOBJECT(103);
	return returnVector;
}

std::vector<unsigned int> DemoProjectComponentManager::GetComponentsIDsInGameObject(GameObject* gameObject)
{
	std::vector<unsigned int> returnVector;

	PB_GET_COMPONENT_IDS(104);
	PB_GET_COMPONENT_IDS(1024);
	PB_GET_COMPONENT_IDS(100);
	PB_GET_COMPONENT_IDS(101);
	PB_GET_COMPONENT_IDS(102);
	PB_GET_COMPONENT_IDS(103);
	return returnVector;
}

std::vector<Component*> DemoProjectComponentManager::GetAllComponents()
{
	std::vector<Component*> vector;
	vector.reserve(ComponentCount());
	cameraSystem.GetAll(vector);
	PB_GET_ALL(textComponentInstances);
	PB_GET_ALL(spaceshipInstances);
	PB_GET_ALL(meshComponentInstances);
	PB_GET_ALL(particleSystemInstances);
	PB_GET_ALL(billboardInstances);
	return vector;
}

void DemoProjectComponentManager::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds)
{
	components.reserve(ComponentCount());
	componentIds.reserve(ComponentCount());

	cameraSystem.GetAll(components);
	Experio::Algorithm::AddNumOf(componentIds, (unsigned int)100, cameraSystem.Size());
	PB_GET_ALL_IDS(textComponentInstances, 104);
	PB_GET_ALL_IDS(spaceshipInstances, 1024);
	PB_GET_ALL_IDS(meshComponentInstances, 101);
	PB_GET_ALL_IDS(particleSystemInstances, 102);
	PB_GET_ALL_IDS(billboardInstances, 103);
}

void DemoProjectComponentManager::GetAllComponents(std::vector<Component*>& components, std::vector<unsigned int>& componentIds, uint8_t sceneIndex)
{
	components.reserve(ComponentCount());
	componentIds.reserve(ComponentCount());

	cameraSystem.GetAllOfScene(components, sceneIndex);
	Experio::Algorithm::AddNumOf(componentIds, (unsigned int)100, cameraSystem.NumInScene(sceneIndex));
	PB_GET_ALL_SCENE_IDS(textComponentInstances, 104);
	PB_GET_ALL_SCENE_IDS(spaceshipInstances, 1024);
	PB_GET_ALL_SCENE_IDS(meshComponentInstances, 101);
	PB_GET_ALL_SCENE_IDS(particleSystemInstances, 102);
	PB_GET_ALL_SCENE_IDS(billboardInstances, 103);
}

unsigned int DemoProjectComponentManager::ComponentCount() const
{
	return cameraSystem.Size() + textComponentInstances.size() + spaceshipInstances.size() + meshComponentInstances.size() + particleSystemInstances.size() + billboardInstances.size();
}
