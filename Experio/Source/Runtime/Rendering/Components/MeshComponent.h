#pragma once

#include "../Materials/MeshMaterial.h"
#include "../../Files/Mesh/MeshReader.h"
#include "glm/glm.hpp"
#include "../../Framework/Framework.h"
#include "../Shader.h"
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
};