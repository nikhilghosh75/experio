#pragma once

#include "MeshReader.h"
#include "../../Rendering/VertexArray.h"
#include "../../Rendering/IndexBuffer.h"
#include "../../Rendering/Managers/MeshManager.h"

class LMeshOperations
{
public:
	static void CalculateBiTangents(
		VertexBuffer& verticies, VertexBuffer& uvs, VertexBuffer& normals,
		VertexBuffer& outTangents, VertexBuffer& outBitangents
	);

	static IndexBuffer* IndexMesh(MeshData& data);

	static IndexBuffer IndexMesh(VertexBuffer& verticies, VertexBuffer& uvs, VertexBuffer& normals);

	static size_t SizeOfMesh(const MeshData& data);
	static size_t SizeOfMesh(const MeshRef& ref);

	static uint8_t GetIndexType(uint32_t numVerticies);
};