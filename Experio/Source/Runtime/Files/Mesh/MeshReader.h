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

class MeshMapData
{
public:
	Texture* albedoMap;
	Texture* normalMap;
	Texture* specularMap;
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
	MeshMapData* mapData;
	bool isIndexed;

	EMeshFileType fileType;

	unsigned int GetTriangleCount()
	{
		return verticies->GetSize() / sizeof(unsigned int);
	}
};

class MeshReader : FileReader<MeshData>
{
public:
	static MeshData* ReadFile(const char* fileName);
};