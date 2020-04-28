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

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::OnNewFrame()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::DrawMesh(const FMeshData & mesh)
{
	if (!mesh.isVisible)
	{
		return;
	}
}

void Renderer::TempDraw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::TempRenderer()
{
	TempProfiler profiler("Rendering");

	OnNewFrame();

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

	VertexArray va;
	VertexBuffer vertexBuffer(positions, sizeof(positions));
	VertexBufferLayout layout;
	layout.PushFloat(3);
	va.AddBuffer(vertexBuffer, layout);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.f / 3.f, 0.1f, 100.0f); // Projection Matrix
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	IndexBuffer indexBuffer(indices, 36);

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	basicShader.Bind();
	basicShader.SetUniformMatrix4("MVP", mvp);

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

	VertexBuffer colorBuffer(g_color_buffer_data, sizeof(g_color_buffer_data));
	VertexBufferLayout colorLayout;
	colorLayout.PushFloat(3);
	va.AddBuffer(colorBuffer, colorLayout);

	TempDraw(va, indexBuffer, basicShader);
	Clear();
}