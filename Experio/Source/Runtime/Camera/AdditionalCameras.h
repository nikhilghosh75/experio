#pragma once
#include "glm/glm.hpp"
#include "../Math/FVector3.h"
#include "../Math/FQuaternion.h"

class AdditionalCameras
{
public:
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;

	static void CalculateViewMatrix(glm::vec3 position, glm::quat rotation);
	static void CalculateViewMatrix(FVector3 position, FQuaternion rotation);

	static void CalculateProjectionMatrix(float fieldOfView, float nearClipPlane, float farClipPlane, float aspectRatio);
};