#pragma once

#include "../FileReader.h"
#include "../../Rendering/VertexBuffer.h"

enum EMeshFileType : uint8_t
{
	OBJ,
	FBX
};

class MeshData : TFileData
{
public:
	VertexBuffer* verticies;
	VertexBuffer* uv;
	VertexBuffer* normals;

	EMeshFileType fileType;

	unsigned int GetTriangleCount()
	{
		return verticies->GetSize() / sizeof(unsigned int);
	}
};

class MeshReader : FileReader<MeshData>
{
	
};