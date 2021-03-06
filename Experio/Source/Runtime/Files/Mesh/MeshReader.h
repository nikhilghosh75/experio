#pragma once

#include "../../Rendering/VertexBuffer.h"
#include "../../Rendering/IndexBuffer.h"
#include "../../Rendering/Texture.h"

enum EMeshFileType : uint8_t
{
	OBJ,
	FBX
};

class MeshData
{
public:
	VertexBuffer* verticies;
	VertexBuffer* uv;
	VertexBuffer* normals;
	VertexBuffer* tangents;
	VertexBuffer* bitangents;
	IndexBuffer* indexBuffer;
	bool isIndexed;

	unsigned int GetTriangleCount() const
	{
		return verticies->GetSize() / sizeof(unsigned int);
	}
};

class MeshReader
{
public:
	static MeshData* ReadFile(const char* fileName);

	static MeshData* ReadFile(unsigned int assetIndex);

	static size_t SerializedSizeOf(const char* filename);

	static size_t SerializedSizeOf(unsigned int assetIndex);
};