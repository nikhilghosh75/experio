#pragma once

#include "../Math/FTransform.h"
#include "Shader.h"
#include "../Files/Mesh/MeshReader.h"
#include "C:\Users\debgh\source\repos\project-bloo\Dependencies\glm\glm\glm.hpp"

class MeshComponent
{
public:
	Shader* meshShader;
	MeshData* meshData;
	FTransform transform;
	bool isVisible;

private:
	glm::mat4 modelMatrix;
public:
	MeshComponent();
	MeshComponent(MeshData* newMeshData, Shader* newShader);

	void SetTransform(FTransform newTransform);

	glm::mat4 GetModelMatrix() const;

	void RecalculateModelMatrix();
};