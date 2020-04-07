#include "../Core/Core.h"
#include "Renderer.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "../Debug/GDebug.h"

unsigned int Renderer::CompileShader(const std::string & source, unsigned int type)
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

unsigned int Renderer::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
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

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::TempRenderer()
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLuint buffer;
	float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	//glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position; \n"
		"\n"
		"void main()\n"
		"{ \n"
		"    gl_Position = position; \n"
		"}\n";
	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) out vec4 color; \n"
		"\n"
		"void main()\n"
		"{ \n"
		"    color = vec4(1.0, 0.0, 0.0, 1.0); \n"
		"}\n";
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}