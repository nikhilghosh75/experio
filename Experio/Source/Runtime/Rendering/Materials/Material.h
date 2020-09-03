#pragma once
#include "../Shader.h"

class Material
{
protected:
	Shader* shader;

public:
	Material()
	{
		this->shader = nullptr;
	}

	Material(Shader* shader)
	{
		this->shader = shader;
	}

	void SetShader(std::string vertex, std::string fragment)
	{
		shader = new Shader(vertex, fragment);
	}

	void Bind()
	{
		shader->Bind();
	}

	virtual void SetInternalUniforms() {}

	~Material()
	{
		delete shader;
	}
};

#define PB_SET_MATERIAL_UNIFORM(_uniformName_, _uniformData_, _uniformFunc_) if(shader->DoesUniformExist(_uniformName_))\
	{\
		shader->_uniformFunc_(_uniformName_, _uniformData_);\
	}