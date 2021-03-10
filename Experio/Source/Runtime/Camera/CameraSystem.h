#pragma once
#include "../Framework/Framework.h"
#include "VirtualCamera.h"
#include <vector>

/// <summary>
/// A system over the Virtual Cameras that control them
/// </summary>

class CameraSystem : public System<VirtualCamera>
{
	std::vector<VirtualCamera> cameras;

	float timeInTransition;

	VirtualCamera* currentCamera;

	static glm::mat4 LerpCamerasViewMatrix(VirtualCamera* c1, VirtualCamera* c2, float t);
	static glm::mat4 LerpCamerasProjectionMatrix(VirtualCamera* c1, VirtualCamera* c2, float t);
public:
	SETUP_SYSTEM(CameraSystem, VirtualCamera);

	float transitionTime;

	virtual void Start() override;

	virtual VirtualCamera* AddComponent(GameObject* gameObject) override;

	virtual VirtualCamera* GetComponent(GameObject* gameObject) override;

	virtual void DeleteComponent(GameObject* gameObject) override;

	virtual void GetAll(std::vector<Component*>& components) override;

	virtual void GetAllOfScene(std::vector<Component*>& components, uint8_t sceneId) override;

	virtual void Update() override;

	virtual unsigned int Size() const override;

	virtual unsigned int NumInScene(uint8_t sceneId) const override;

	VirtualCamera* GetCurrentCamera();

	glm::mat4 currentViewMatrix;
	glm::mat4 currentProjectionMatrix;
};