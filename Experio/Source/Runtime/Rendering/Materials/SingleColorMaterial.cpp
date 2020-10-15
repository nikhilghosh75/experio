#include "SingleColorMaterial.h"

SingleColorMaterial::SingleColorMaterial()
{
	this->shader = nullptr;
}

SingleColorMaterial::SingleColorMaterial(Shader * shader)
{
	this->shader = shader;
}

void SingleColorMaterial::SetInternalUniforms()
{

}

void SingleColorMaterial::SetInternalBuffers(VertexArray & vertexArray)
{
	VertexBufferLayout colorLayout;
	colorLayout.PushFloat(4);
	vertexArray.AddBuffer(colorBuffer, colorLayout);
}
