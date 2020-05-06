#include "Shader.h"
#include "GL/glew.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../Debug/GDebug.h"


Shader::Shader(const std::string & vertexShaderFilepath, const std::string & fragmentShaderFilepath)
{
	this->vertexShaderFilepath = vertexShaderFilepath;
	this->fragmentShaderFilepath = fragmentShaderFilepath;
	std::string vertexShader = ParseShader(vertexShaderFilepath);
	std::string fragmentShader = ParseShader(fragmentShaderFilepath);
	this->rendererID = CreateShader(vertexShader, fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(this->rendererID);
}

void Shader::Bind() const
{
	glUseProgram(this->rendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniformVec4(const std::string & name, glm::vec4 vec) const
{
	//glUniform4fv(GetUniformLocation(name), 1, vec.);
}

void Shader::SetUniformMatrix4(const std::string & name, glm::mat4 mat) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::CompileShader(const std::string & source, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		GDebug::LogError("Failed to compile shader!" + std::string(message));
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

std::string Shader::ParseShader(const std::string& filepath)
{
	std::stringstream stringStream;
	std::ifstream inStream(filepath);
	std::string temp;
	while (std::getline(inStream, temp))
	{
		stringStream << temp << "\n";
	}
	return stringStream.str();
}

unsigned int Shader::GetUniformLocation(const std::string & name) const
{
	return glGetUniformLocation(rendererID, name.c_str());
}
