#pragma once
#include "glm/glm.hpp"
#include "../Math/FVector3.h"
#include "../Math/FQuaternion.h"

struct FRay;
struct FVector2;

class AdditionalCameras
{
public:
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;
	static glm::vec3 cameraPosition;

	static void CalculateViewMatrix(glm::vec3 position, glm::quat rotation);
	static void CalculateViewMatrix(FVector3 position, FQuaternion rotation);

	static void CalculateProjectionMatrix(float fieldOfView, float nearClipPlane, float farClipPlane, float aspectRatio);

	static FRay ScreenPointToRay(FVector2 point);
};