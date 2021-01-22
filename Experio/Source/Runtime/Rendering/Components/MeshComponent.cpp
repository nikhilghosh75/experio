#include "MeshComponent.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../../Files/Mesh/MeshReader.h"
#include "../../Camera/CameraSystem.h"
#include "../Renderer.h"

MeshComponent::MeshComponent()
{
	this->isVisible = true;
}

MeshComponent::MeshComponent(GameObject * object)
{
	this->isVisible = true;
	this->gameObject = object;
}

MeshComponent::MeshComponent(MeshRef newMeshData)
{
	this->isVisible = true;
	this->meshData = newMeshData;
}

glm::mat4 MeshComponent::GetModelMatrix() const
{
	return this->modelMatrix;
}

void MeshComponent::Start()
{

}

void MeshComponent::Update()
{
	RecalculateModelMatrix();

	Renderer::Get()->DrawMesh(*this);
}

void MeshComponent::RecalculateModelMatrix()
{
	FVector3 position = gameObject->GetPosition();
	FQuaternion rotation = gameObject->GetRotation();
	FVector3 scale = gameObject->GetScale();

	glm::mat4 translationMatrix = glm::translate((glm::vec3)position);
	glm::mat4 rotationMatrix = glm::toMat4((glm::quat)rotation);
	glm::mat4 scaleMatrix = glm::scale((glm::vec3)scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 MeshComponent::CalculateModelMatrix(FVector3 position, FQuaternion rotation, FVector3 scale)
{
	glm::mat4 translationMatrix = glm::translate((glm::vec3)position);
	glm::mat4 rotationMatrix = glm::toMat4((glm::quat)rotation);
	glm::mat4 scaleMatrix = glm::scale((glm::vec3)scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 MeshComponent::CalculateModelMatrix(const GameObject & gameObject)
{
	return CalculateModelMatrix(gameObject.GetPosition(), gameObject.GetRotation(), gameObject.GetScale());
}
