#pragma once
#include "MeshMaterial.h"
#include "../VertexBuffer.h"

class SingleColorMaterial : public MeshMaterial
{
public:
	SingleColorMaterial();
	SingleColorMaterial(Shader* shaders);

	VertexBuffer* colorBuffer;

	virtual void SetInternalUniforms() override;

	virtual void SetInternalBuffers(VertexArray& vertexArray) override;
};