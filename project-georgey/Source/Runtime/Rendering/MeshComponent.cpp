#include "MeshComponent.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

MeshComponent::MeshComponent()
{
	this->isVisible = true;
}

MeshComponent::MeshComponent(MeshData * newMeshData, Shader * newShader)
{
	this->isVisible = true;
	this->meshData = newMeshData;
	this->meshShader = newShader;
}

void MeshComponent::SetTransform(FTransform newTransform)
{
	this->transform = newTransform;
	//this->transform.OnTransformChange.AddListener(this->*(MeshComponent::RecalculateModelMatrix));
	RecalculateModelMatrix();
}

glm::mat4 MeshComponent::GetModelMatrix() const
{
	return this->modelMatrix;
}

void MeshComponent::RecalculateModelMatrix()
{
	FVector3 position = transform.GetPosition();
	FQuaternion rotation = transform.GetRotation();
	FVector3 scale = transform.GetScale();

	glm::mat4 translationMatrix = glm::translate((glm::vec3)position);
	glm::mat4 rotationMatrix = glm::toMat4((glm::quat)rotation);
	glm::mat4 scaleMatrix = glm::scale((glm::vec3)scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}
