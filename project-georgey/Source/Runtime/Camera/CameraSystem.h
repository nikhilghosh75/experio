#pragma once
#include "../Framework/Framework.h"
#include "VirtualCamera.h"
#include <vector>

class CameraSystem
{
	static std::vector<VirtualCamera*> cameras;

	static float timeInTransition;

	static VirtualCamera* GetCurrentCamera();
	static VirtualCamera* currentCamera;

	static glm::mat4 LerpCamerasViewMatrix(VirtualCamera* c1, VirtualCamera* c2, float t);
	static glm::mat4 LerpCamerasProjectionMatrix(VirtualCamera* c1, VirtualCamera* c2, float t);
public:
	static float transitionTime;

	static void RegisterCamera(VirtualCamera* camera);

	static void Update();

	static glm::mat4 currentViewMatrix;
	static glm::mat4 currentProjectionMatrix;
};