#pragma once

#include "../Math/FTransform.h"
#include "Materials/MeshMaterial.h"
#include "../Files/Mesh/MeshReader.h"
#include "C:\Users\debgh\source\repos\project-bloo\Dependencies\glm\glm\glm.hpp"
#include "../Framework/Framework.h"
#include "Shader.h"

class MeshComponent : public Component
{
public:
	MeshMaterial* material = nullptr;
	MeshData* meshData = nullptr;
	bool isVisible;

private:
	glm::mat4 modelMatrix;
public:
	MeshComponent();
	MeshComponent(GameObject* object);
	MeshComponent(MeshData* newMeshData);

	glm::mat4 GetModelMatrix() const;

	virtual void Start() override;
	virtual void Update() override;

	void RecalculateModelMatrix();
};