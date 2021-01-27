#pragma once

#include "../Materials/MeshMaterial.h"
#include "../../Files/Mesh/MeshReader.h"
#include "glm/glm.hpp"
#include "../../Framework/Framework.h"
#include "../Shaders/Shader.h"
#include "../Managers/MeshManager.h"

class MeshComponent : public Component
{
public:
	MeshMaterial* material = nullptr;
	MeshRef meshData;
	bool isVisible;

private:
	glm::mat4 modelMatrix;
public:
	MeshComponent();
	MeshComponent(GameObject* object);
	MeshComponent(MeshRef newMeshData);

	glm::mat4 GetModelMatrix() const;

	virtual void Start() override;
	virtual void Update() override;

	void RecalculateModelMatrix();

	static glm::mat4 CalculateModelMatrix(FVector3 position, FQuaternion rotation, FVector3 scale);
	static glm::mat4 CalculateModelMatrix(const GameObject& gameObject);
};