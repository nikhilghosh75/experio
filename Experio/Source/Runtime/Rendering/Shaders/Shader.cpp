#include "Shader.h"
#include "GL/glew.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../../Debug/Debug.h"
#include "ShaderReader.h"

uint32_t Shader::numShadersLoaded = 0;

Shader::Shader()
{
	this->rendererID = 0;
}

Shader::Shader(unsigned int rendererID)
{
	this->rendererID = rendererID;
	numShadersLoaded++;
}

Shader::~Shader()
{
	glDeleteProgram(this->rendererID);
	numShadersLoaded--;
}

void Shader::Bind() const
{
	glUseProgram(this->rendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniformInt(const std::string & name, int i) const
{
	glUniform1i(GetUniformLocation(name), i);
}

void Shader::SetUniformFloat(const std::string & name, float f) const
{
	glUniform1f(GetUniformLocation(name), f);
}

void Shader::SetUniformVec2(const std::string & name, glm::vec2 vec) const
{
	glUniform2fv(GetUniformLocation(name), 1, (GLfloat*)&vec);
}

void Shader::SetUniformVec3(const std::string & name, glm::vec3 vec) const
{
	glUniform3fv(GetUniformLocation(name), 1, (GLfloat*)&vec);
}

void Shader::SetUniformVec4(const std::string & name, glm::vec4 vec) const
{
	glUniform4fv(GetUniformLocation(name), 1, (GLfloat*)&vec);
}

void Shader::SetUniformMatrix2(const std::string & name, glm::mat2 mat) const
{
	glUniformMatrix2fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniformMatrix3(const std::string & name, glm::mat3 mat) const
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetUniformMatrix4(const std::string & name, glm::mat4 mat) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::GetUniformLocation(const std::string & name) const
{
	unsigned int i = glGetUniformLocation(rendererID, name.c_str());
	return i;
}

bool Shader::DoesUniformExist(const std::string & name) const
{
	return glGetUniformLocation(rendererID, name.c_str()) != -1;
}

size_t Shader::SizeOfLoadedShaders()
{
	return numShadersLoaded * sizeof(Shader);
}
