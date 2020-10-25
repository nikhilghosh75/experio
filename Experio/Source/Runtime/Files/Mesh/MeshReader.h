#pragma once

#include "../FileReader.h"
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

	EMeshFileType fileType;

	unsigned int GetTriangleCount() const
	{
		return verticies->GetSize() / sizeof(unsigned int);
	}
};

class MeshReader : FileReader<MeshData>
{
public:
	static MeshData* ReadFile(const char* fileName);
};