#include "MeshData.h"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

FMeshData::FMeshData()
{
	this->isVisible = true;
}

FMeshData::FMeshData(const VertexBuffer & vertices, const IndexBuffer & indices)
{
	this->vertices = vertices;
	this->indices = indices;
	this->transform = FTransform();
	this->isVisible = true;
}

FMeshData::FMeshData(const VertexBuffer & vertices, const IndexBuffer & indices, const FTransform & transform)
{
	this->vertices = vertices;
	this->indices = indices;
	this->transform = transform;
	this->isVisible = true;
}

void FMeshData::SetTransform(const FTransform & transform)
{
	this->transform = transform;
}

glm::mat4 FMeshData::GetModelMatrix() const
{
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), (glm::vec3)(this->transform.position));
	glm::mat4 rotationMatrix = glm::toMat4((glm::quat) this->transform.rotation);
	glm::mat4 scaleMatrix = glm::scale((glm::vec3)this->transform.scale);
	return translationMatrix * rotationMatrix * scaleMatrix;
}
