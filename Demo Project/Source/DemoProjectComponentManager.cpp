#include "DemoProjectComponentManager.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Debug/Debug.h"

void DemoProjectComponentManager::Start()
{
	cameraSystem.Start();
	PB_START(textComponentInstances);
	PB_START(spaceshipInstances);
	PB_START(imageComponentInstances);
	PB_START(progressBarInstances);
	PB_START(panelInstances);
	PB_START(buttonInstances);
	PB_START(meshComponentInstances);
	PB_START(checkBoxInstances);
	PB_START(particleComponentInstances);
	PB_START(sliderInstances);
	PB_START(billboardInstances);
}

void DemoProjectComponentManager::Update()
{
	cameraSystem.Update();
	PB_UPDATE(spaceshipInstances);
	PB_UPDATE(meshComponentInstances);
	PB_UPDATE(particleComponentInstances);
	PB_UPDATE(billboardInstances);
	PB_UPDATE(textComponentInstances);
	PB_UPDATE(imageComponentInstances);
	PB_UPDATE(progressBarInstances);
	PB_UPDATE(panelInstances);
	PB_UPDATE(buttonInstances);
	PB_UPDATE(checkBoxInstances);
	PB_UPDATE(sliderInstances);
	UIQueue::RenderUI();
}

void DemoProjectComponentManager::RenderScene()
{
	cameraSystem.Update();
	PB_UPDATE(meshComponentInstances);
	PB_UPDATE(particleComponentInstances);
	PB_UPDATE(billboardInstances);
	PB_UPDATE(buttonInstances);
	PB_UPDATE(checkBoxInstances);
	PB_UPDATE(imageComponentInstances);
	PB_UPDATE(textComponentInstances);
	PB_UPDATE(progressBarInstances);
	PB_UPDATE(panelInstances);
	UIQueue::RenderUI();
}

Component* DemoProjectComponentManager::AddComponent(GameObject* gameObject, unsigned int classId)
{
	switch(classId)
	{
		case 100: return cameraSystem.AddComponent(gameObject);
		case 104: PB_ADD_COMPONENT(textComponentInstances);
		case 1024: PB_ADD_COMPONENT(spaceshipInstances);
		case 105: PB_ADD_COMPONENT(imageComponentInstances);
		case 106: PB_ADD_COMPONENT(progressBarInstances);
		case 107: PB_ADD_COMPONENT(panelInstances);
		case 108: PB_ADD_COMPONENT(buttonInstances);
		case 101: PB_ADD_COMPONENT(meshComponentInstances);
		case 109: PB_ADD_COMPONENT(checkBoxInstances);
		case 102: PB_ADD_COMPONENT(particleComponentInstances);
		case 110: PB_ADD_COMPONENT(sliderInstances);
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
		case 105: PB_GET_COMPONENT(imageComponentInstances);
		case 106: PB_GET_COMPONENT(progressBarInstances);
		case 107: PB_GET_COMPONENT(panelInstances);
		case 108: PB_GET_COMPONENT(buttonInstances);
		case 101: PB_GET_COMPONENT(meshComponentInstances);
		case 109: PB_GET_COMPONENT(checkBoxInstances);
		case 102: PB_GET_COMPONENT(particleComponentInstances);
		case 110: PB_GET_COMPONENT(sliderInstances);
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
		case 105: PB_DELETE_COMPONENT(imageComponentInstances);
		case 106: PB_DELETE_COMPONENT(progressBarInstances);
		case 107: PB_DELETE_COMPONENT(panelInstances);
		case 108: PB_DELETE_COMPONENT(buttonInstances);
		case 101: PB_DELETE_COMPONENT(meshComponentInstances);
		case 109: PB_DELETE_COMPONENT(checkBoxInstances);
		case 102: PB_DELETE_COMPONENT(particleComponentInstances);
		case 110: PB_DELETE_COMPONENT(sliderInstances);
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
		case 105: PB_GET_COMPONENT_INDEX(imageComponentInstances);
		case 106: PB_GET_COMPONENT_INDEX(progressBarInstances);
		case 107: PB_GET_COMPONENT_INDEX(panelInstances);
		case 108: PB_GET_COMPONENT_INDEX(buttonInstances);
		case 101: PB_GET_COMPONENT_INDEX(meshComponentInstances);
		case 109: PB_GET_COMPONENT_INDEX(checkBoxInstances);
		case 102: PB_GET_COMPONENT_INDEX(particleComponentInstances);
		case 110: PB_GET_COMPONENT_INDEX(sliderInstances);
		case 103: PB_GET_COMPONENT_INDEX(billboardInstances);
	}
}

void DemoProjectComponentManager::OnGameObjectDeleted(GameObject* gameObject)
{
	bool foundComponent = false;

	cameraSystem.OnGameObjectDeleted(gameObject);
	PB_DELETE_COMPONENT(textComponentInstances); foundComponent = false;
	PB_DELETE_COMPONENT(spaceshipInstances); foundComponent = false;
	PB_DELETE_COMPONENT(imageComponentInstances); foundComponent = false;
	PB_DELETE_COMPONENT(progressBarInstances); foundComponent = false;
	PB_DELETE_COMPONENT(panelInstances); foundComponent = false;
	PB_DELETE_COMPONENT(buttonInstances); foundComponent = false;
	PB_DELETE_COMPONENT(meshComponentInstances); foundComponent = false;
	PB_DELETE_COMPONENT(checkBoxInstances); foundComponent = false;
	PB_DELETE_COMPONENT(particleComponentInstances); foundComponent = false;
	PB_DELETE_COMPONENT(sliderInstances); foundComponent = false;
	PB_DELETE_COMPONENT(billboardInstances); foundComponent = false;
}

std::vector<Component*> DemoProjectComponentManager::GetComponentsInGameObject(GameObject * gameObject)
{
	std::vector<Component*> returnVector;
	Component* component;
	returnVector.reserve(ComponentCount());

	PB_GET_COMPONENT_GAMEOBJECT(104);
	PB_GET_COMPONENT_GAMEOBJECT(1024);
	PB_GET_COMPONENT_GAMEOBJECT(105);
	PB_GET_COMPONENT_GAMEOBJECT(106);
	PB_GET_COMPONENT_GAMEOBJECT(107);
	PB_GET_COMPONENT_GAMEOBJECT(100);
	PB_GET_COMPONENT_GAMEOBJECT(108);
	PB_GET_COMPONENT_GAMEOBJECT(101);
	PB_GET_COMPONENT_GAMEOBJECT(109);
	PB_GET_COMPONENT_GAMEOBJECT(102);
	PB_GET_COMPONENT_GAMEOBJECT(110);
	PB_GET_COMPONENT_GAMEOBJECT(103);
	return returnVector;
}

std::vector<unsigned int> DemoProjectComponentManager::GetComponentsIDsInGameObject(GameObject* gameObject)
{
	std::vector<unsigned int> returnVector;

	PB_GET_COMPONENT_IDS(104);
	PB_GET_COMPONENT_IDS(1024);
	PB_GET_COMPONENT_IDS(105);
	PB_GET_COMPONENT_IDS(106);
	PB_GET_COMPONENT_IDS(107);
	PB_GET_COMPONENT_IDS(100);
	PB_GET_COMPONENT_IDS(108);
	PB_GET_COMPONENT_IDS(101);
	PB_GET_COMPONENT_IDS(109);
	PB_GET_COMPONENT_IDS(102);
	PB_GET_COMPONENT_IDS(110);
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
	PB_GET_ALL(imageComponentInstances);
	PB_GET_ALL(progressBarInstances);
	PB_GET_ALL(panelInstances);
	PB_GET_ALL(buttonInstances);
	PB_GET_ALL(meshComponentInstances);
	PB_GET_ALL(checkBoxInstances);
	PB_GET_ALL(particleComponentInstances);
	PB_GET_ALL(sliderInstances);
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
	PB_GET_ALL_IDS(imageComponentInstances, 105);
	PB_GET_ALL_IDS(progressBarInstances, 106);
	PB_GET_ALL_IDS(panelInstances, 107);
	PB_GET_ALL_IDS(buttonInstances, 108);
	PB_GET_ALL_IDS(meshComponentInstances, 101);
	PB_GET_ALL_IDS(checkBoxInstances, 109);
	PB_GET_ALL_IDS(particleComponentInstances, 102);
	PB_GET_ALL_IDS(sliderInstances, 110);
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
	PB_GET_ALL_SCENE_IDS(imageComponentInstances, 105);
	PB_GET_ALL_SCENE_IDS(progressBarInstances, 106);
	PB_GET_ALL_SCENE_IDS(panelInstances, 107);
	PB_GET_ALL_SCENE_IDS(buttonInstances, 108);
	PB_GET_ALL_SCENE_IDS(meshComponentInstances, 101);
	PB_GET_ALL_SCENE_IDS(checkBoxInstances, 109);
	PB_GET_ALL_SCENE_IDS(particleComponentInstances, 102);
	PB_GET_ALL_SCENE_IDS(sliderInstances, 110);
	PB_GET_ALL_SCENE_IDS(billboardInstances, 103);
}

unsigned int DemoProjectComponentManager::ComponentCount() const
{
	return cameraSystem.Size() + textComponentInstances.size() + spaceshipInstances.size() + imageComponentInstances.size() + progressBarInstances.size() + panelInstances.size() + buttonInstances.size() + meshComponentInstances.size() + checkBoxInstances.size() + particleComponentInstances.size() + sliderInstances.size() + billboardInstances.size();
}
