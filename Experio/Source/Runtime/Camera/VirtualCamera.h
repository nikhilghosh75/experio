#pragma once
#include "../Framework/Framework.h"
#include <glm/glm.hpp>

struct FRay;
struct FVector2;

/// <summary>
/// A camera that is only active in certain circumstances
/// As many of them can be in a scene as you want
/// </summary>

class VirtualCamera : public Component
{
public:
	VirtualCamera(GameObject* object);

	float priority = 1.f;

	float fieldOfView; // Degrees
	float nearClipPlane = 0.1f;
	float farClipPlane = 1000.f;

	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;

	static glm::mat4 CalculateViewMatrix(glm::vec3 position, glm::quat rotation);
	static glm::mat4 CalculateProjectionMatrix(float fieldOfView, float nearClipPlane, float farClipPlane);

	FRay ScreenPointToRay(float x, float y);
	FRay ScreenPointToRay(FVector2 point);
};