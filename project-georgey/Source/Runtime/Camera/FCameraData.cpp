#include "FCameraData.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

FCameraData::FCameraData()
{
	this->fieldOfView = 90.f;
}

FCameraData::FCameraData(float fieldOfView)
{
	this->fieldOfView = fieldOfView;
}

FCameraData::FCameraData(FTransform cameraTransform, float fieldOfView)
{
	this->cameraTransform = cameraTransform;
	this->fieldOfView = fieldOfView;
}

FCameraData::FCameraData(FVector3 position, FQuaternion rotation, float fieldOfView)
{
	this->cameraTransform = FTransform(position, rotation);
	this->fieldOfView = fieldOfView;
}

glm::mat4 FCameraData::GetViewMatrix() const
{
	return (glm::mat4)cameraTransform.GetRotation() * glm::translate(glm::mat4(), (glm::vec3)(cameraTransform.GetPosition() * -1.f));
}
