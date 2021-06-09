#pragma once
#include "Runtime/Framework/ComponentManager.h"
#include "Runtime/DefaultComponents.h"

#include "../Source\Components\Spaceship.h"
class DemoProjectComponentManager : public ComponentManager
{
	public:
	std::vector<TextComponent> textComponentInstances;

	std::vector<Spaceship> spaceshipInstances;

	std::vector<ImageComponent> imageComponentInstances;

	std::vector<ProgressBar> progressBarInstances;

	std::vector<Panel> panelInstances;

	std::vector<Button> buttonInstances;

	std::vector<MeshComponent> meshComponentInstances;

	std::vector<ParticleComponent> particleComponentInstances;

	std::vector<Billboard> billboardInstances;

	CameraSystem cameraSystem;

	virtual void Start() override;
	virtual void Update() override;
	virtual void RenderScene() override;
	virtual Component* AddComponent(GameObject* gameObject,unsigned int classId) override;
	virtual Component* GetComponent(GameObject* gameObject,unsigned int classId) override;
	virtual Component* GetComponentAtIndex(unsigned int classId,unsigned int index) override;
	virtual void DeleteComponent(GameObject* gameObject,unsigned int classId) override;
	virtual void OnGameObjectDeleted(GameObject* gameObject) override;
	virtual std::vector<unsigned int> GetComponentsIDsInGameObject(GameObject* gameObject) override;
	virtual std::vector<Component*> GetComponentsInGameObject(GameObject* gameObject) override;
	virtual std::vector<Component*> GetAllComponents() override;
	virtual void GetAllComponents(std::vector<Component*>& components,std::vector<unsigned int>& componentIds) override;
	virtual void GetAllComponents(std::vector<Component*>& components,std::vector<unsigned int>& componentIds,uint8_t sceneIndex) override;
	virtual unsigned int ComponentCount() const override;

};
