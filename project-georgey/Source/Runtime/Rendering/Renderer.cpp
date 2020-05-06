#include "../Core/Core.h"
#include "Renderer.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "../Math/LMath.h"
#include "../Debug/GDebug.h"
#include "../Debug/TempProfiler.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../Core/GWindow.h"
#include "../Core/LWindowOperations.h"

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
	defaultVertexLayout.PushFloat(3);
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

void Renderer::DrawMesh(const FMeshData & mesh, const FCameraData& cameraData)
{
	TempProfiler("Rendering Cube");

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!mesh.isVisible)
	{
		return;
	}

	glm::mat4 modelMatrix = mesh.GetModelMatrix();

	//glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 viewMatrix = (glm::mat4)cameraData.cameraTransform.rotation * glm::translate(glm::mat4(), (glm::vec3)(cameraData.cameraTransform.position * -1.f));

	mesh.vertices->Bind();

	FWindowData data = GWindow::GetWindowData();
	float aspectRatio = LWindowOperations::GetAspectRatio(data);
	glm::mat4 projectionMatrix = glm::perspective(LMath::DegreesToRadians(cameraData.fieldOfView), aspectRatio, cameraData.nearClipPlane, cameraData.farClipPlane);

	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	basicShader.Bind();
	basicShader.SetUniformMatrix4("MVP", MVP);

	VertexBufferLayout positionLayout;
	positionLayout.PushFloat(3);
	VertexArray va;
	va.AddBuffer(mesh.vertices, positionLayout);

	TempDraw(&va, mesh.indices, &basicShader);

	LogRenderingError();
}

void Renderer::TempDraw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const
{
	shader->Bind();
	va->Bind();
	ib->Bind();
	glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
}

FMeshData* Renderer::TempSetup()
{
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

	VertexBuffer* vertexBuffer = new VertexBuffer(positions, 96);
	IndexBuffer* indexBuffer = new IndexBuffer(indices, 36);

	FMeshData* returnData = new FMeshData(vertexBuffer, indexBuffer);

	return returnData;
}


void Renderer::TempRenderer()
{
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

	VertexBuffer vb(positions, sizeof(positions));
	VertexBufferLayout positionLayout;
	positionLayout.PushFloat(3);
	VertexArray va;
	va.AddBuffer(&vb, positionLayout);

	IndexBuffer ib(indices, 36);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), 4.f / 3.f, 0.1f, 100.0f); // Projection Matrix
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	basicShader.Bind();
	basicShader.SetUniformMatrix4("MVP", mvp);

	TempDraw(&va, &ib, &basicShader);
}