#include "../Core/Core.h"
#include "Renderer.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "../Debug/GDebug.h"
#include "../Debug/TempProfiler.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

void Renderer::LogRenderingError()
{
	GLenum currentError = glGetError();
	if (currentError != GL_NO_ERROR)
	{
		GDebug::LogError("OPENGL Error " + to_string(currentError));
	}
}

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

std::string vertexShader =
	"#version 330 core\n"
	"\n"
	"layout(location = 0) in vec4 position; \n"
	"layout(location = 1) in vec3 vertexColor; \n"
	"uniform mat4 MVP; \n"
	"out vec3 fragmentColor; \n"
	"\n"
	"void main()\n"
	"{ \n"
	"    gl_Position = MVP * position; \n"
	"	 fragmentColor = vertexColor; \n"
	"}\n";
std::string fragmentShader =
	"#version 330 core\n"
	"\n"
	"out vec3 color; \n"
	"in vec3 fragmentColor; \n"
	"\n"
	"void main()\n"
	"{ \n"
	"    color = fragmentColor; \n"
	"}\n";

void Renderer::TempRenderer()
{
	TempProfiler profiler("Rendering");
	GLuint buffer;

	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float positions[] = {
	-1.0f,-1.0f,-1.0f, // 0
	-1.0f,-1.0f, 1.0f, // 1
	-1.0f, 1.0f, 1.0f, // 2
	1.0f, 1.0f,-1.0f, // 3
	-1.0f, 1.0f,-1.0f, // 4
	1.0f,-1.0f, 1.0f, // 5
	1.0f,-1.0f,-1.0f, // 6
	1.0f, 1.0f, 1.0f, // 7
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		3, 0, 4,
		5, 0, 6,
		3, 6, 0,
		0, 2, 4,
		5, 1, 0,
		2, 1, 5,
		7, 6, 3,
		6, 7, 5,
		7, 3, 4,
		7, 4, 1,
		7, 2, 5
	};

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.f / 3.f, 0.1f, 100.0f); // Projection Matrix
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.3875f, glm::vec3(0, 0, 1)); // GLM is down columns

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);

	unsigned int indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	std::string vertexShader =
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position; \n"
		"layout(location = 1) in vec3 vertexColor; \n"
		"uniform mat4 MVP; \n"
		"out vec3 fragmentColor; \n"
		"\n"
		"void main()\n"
		"{ \n"
		"    gl_Position = MVP * position; \n"
		"	 fragmentColor = vertexColor; \n"
		"}\n";
	std::string fragmentShader =
		"#version 330 core\n"
		"\n"
		"out vec3 color; \n"
		"in vec3 fragmentColor; \n"
		"\n"
		"void main()\n"
		"{ \n"
		"    color = fragmentColor; \n"
		"}\n";
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	GLuint matrixID = glGetUniformLocation(shader, "MVP");
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

	GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
	};

	GLuint colorBuffer;
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDeleteVertexArrays(1, &vertexArrayID);

}