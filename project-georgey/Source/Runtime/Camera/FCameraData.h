#pragma once
#include "../Math/FTransform.h"
#include "C:\Users\debgh\source\repos\project-bloo\Dependencies\glm\glm\glm.hpp"


struct FCameraData
{
	FTransform cameraTransform;
	float fieldOfView;
	float nearClipPlane = 0.1f;
	float farClipPlane = 100.f;

	FCameraData();
	FCameraData(float fieldOfView);
	FCameraData(FTransform cameraTransform, float fieldOfView);
	FCameraData(FVector3 position, FQuaternion rotation, float fieldOfView);

	glm::mat4 GetViewMatrix() const;
};