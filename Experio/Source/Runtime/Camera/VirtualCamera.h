#pragma once
#include "../Framework/Framework.h"
#include "C:\Users\debgh\source\repos\project-bloo\Dependencies\glm\glm\glm.hpp"

class VirtualCamera : public Component
{
public:
	VirtualCamera(GameObject* object);

	float priority = 1.f;

	float fieldOfView;
	float nearClipPlane = 0.1f;
	float farClipPlane = 1000.f;

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

	static glm::mat4 CalculateViewMatrix(glm::vec3 position, glm::quat rotation);
	static glm::mat4 CalculateProjectionMatrix(float fieldOfView, float nearClipPlane, float farClipPlane);
};