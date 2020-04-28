#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>
#include "../Math/FVector3.h"
#include "../Math/FQuaternion.h"
#include "../Math/FTransform.h"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/glm.hpp"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/glm/glm/mat4x4.hpp"

struct FMeshData
{
	VertexBuffer vertices;
	IndexBuffer indices;
	FTransform transform;
	bool isVisible;

	FMeshData();
	FMeshData(const VertexBuffer& vertices, const IndexBuffer& indices);
	FMeshData(const VertexBuffer& vertices, const IndexBuffer& indices, const FTransform& transform);

	void SetTransform(const FTransform& transform);

	glm::mat4 GetModelMatrix();
};