#pragma once
#include "../Shader.h"
#include "../VertexArray.h"

class Material
{
protected:
	Shader* shader;
	uint64_t id;

public:
	Material()
	{
		this->shader = nullptr;
	}

	Material(Shader* shader)
	{
		this->shader = shader;
	}

	Material(Shader* shader, uint64_t id)
	{
		this->shader = shader;
		this->id = id;
	}

	void SetShader(std::string vertex, std::string fragment)
	{
		shader = new Shader(vertex, fragment);
	}

	void Bind()
	{
		shader->Bind();
	}

	uint64_t GetID() const
	{
		return id;
	}

	virtual void SetInternalUniforms() {}
	virtual void SetInternalBuffers(VertexArray& vertexArray) {};

	~Material()
	{
		delete shader;
	}
};

#define PB_SET_MATERIAL_UNIFORM(_uniformName_, _uniformData_, _uniformFunc_) if(shader->DoesUniformExist(_uniformName_))\
	{\
		shader->_uniformFunc_(_uniformName_, _uniformData_);\
	}