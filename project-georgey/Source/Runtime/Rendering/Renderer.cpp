﻿#include "../Core/Core.h"
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
#include <fstream>
#include "../Files/Images/ImageReader.h"
#include "../Files/Images/BMPReader.h"
#include "../Files/Mesh/OBJReader.h"
#include "Texture.h"

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

void Renderer::DrawMesh(const MeshComponent & mesh, const FCameraData & cameraData)
{
	TempProfiler("Rendering Mesh");

	if (!mesh.isVisible)
	{
		return;
	}

	glm::mat4 modelMatrix = mesh.GetModelMatrix();
	glm::mat4 viewMatrix = cameraData.GetViewMatrix();

	FWindowData data = GWindow::GetWindowData();
	float aspectRatio = LWindowOperations::GetAspectRatio(data);
	glm::mat4 projectionMatrix = glm::perspective(LMath::DegreesToRadians(cameraData.fieldOfView), aspectRatio, cameraData.nearClipPlane, cameraData.farClipPlane);

	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	mesh.meshShader->Bind();
	mesh.meshShader->SetUniformMatrix4("MVP", MVP);

	VertexArray va;

	VertexBufferLayout positionLayout;
	positionLayout.PushFloat(3);
	VertexBufferLayout uvLayout;
	uvLayout.PushFloat(2);
	VertexBufferLayout normalLayout;
	normalLayout.PushFloat(3);

	va.AddBuffer(mesh.meshData->verticies, positionLayout);
	va.AddBuffer(mesh.meshData->uv, uvLayout);
	va.AddBuffer(mesh.meshData->normals, normalLayout);

	glDrawArrays(GL_TRIANGLES, 0, mesh.meshData->GetTriangleCount());
}

void Renderer::TempDraw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const
{
	shader->Bind();
	va->Bind();
	ib->Bind();
	glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::TempDraw(const VertexArray * va, const Shader * shader, int count) const
{
	shader->Bind();
	va->Bind();
	glDrawArrays(GL_TRIANGLES, 0, (unsigned int)count);
}


void Renderer::TempRenderer()
{
	TempProfiler("Rendering Textured Cube");

	BMPReader bmpReader;

	Clear();

	VertexArray va;
	va.Bind();

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	basicShader.Bind();

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 2.f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f, // 0
		-1.0f,-1.0f, 1.0f, // 1
		-1.0f, 1.0f, 1.0f, // 2
		 1.0f, 1.0f,-1.0f, // 3
		-1.0f,-1.0f,-1.0f, // 0
		-1.0f, 1.0f,-1.0f, // 4
		 1.0f,-1.0f, 1.0f, // 5
		-1.0f,-1.0f,-1.0f, // 0
		 1.0f,-1.0f,-1.0f, // 6
		 1.0f, 1.0f,-1.0f, // 3
		 1.0f,-1.0f,-1.0f, // 6
		-1.0f,-1.0f,-1.0f, // 0
		-1.0f,-1.0f,-1.0f, // 0
		-1.0f, 1.0f, 1.0f, // 2
		-1.0f, 1.0f,-1.0f, // 4
		 1.0f,-1.0f, 1.0f, // 5
		-1.0f,-1.0f, 1.0f, // 1
		-1.0f,-1.0f,-1.0f, // 0
		-1.0f, 1.0f, 1.0f, // 2
		-1.0f,-1.0f, 1.0f, // 1
		 1.0f,-1.0f, 1.0f, // 5
		 1.0f, 1.0f, 1.0f, // 7
		 1.0f,-1.0f,-1.0f, // 6
		 1.0f, 1.0f,-1.0f, // 3
		 1.0f,-1.0f,-1.0f, // 6
		 1.0f, 1.0f, 1.0f, // 7
		 1.0f,-1.0f, 1.0f, // 5
		 1.0f, 1.0f, 1.0f, // 7
		 1.0f, 1.0f,-1.0f, // 3
		-1.0f, 1.0f,-1.0f, // 4
		 1.0f, 1.0f, 1.0f, // 7
		-1.0f, 1.0f,-1.0f, // 4
		-1.0f, 1.0f, 1.0f, // 1
		 1.0f, 1.0f, 1.0f, // 7
		-1.0f, 1.0f, 1.0f, // 2
		 1.0f,-1.0f, 1.0f  // 5
	};

	// Two UV coordinates for each vertex. They were created with Blender.
	static const GLfloat g_uv_buffer_data[] = {
		0.000000f, 0.333333f,
		0.250000f, 0.333333f,
		0.250000f, 0.666667f,
		0.999930f, 0.329114f,
		0.667979f, 0.666667f,
		1.000000f, 0.666667f,
		0.667979f, 0.666667f,
		0.336024f, 1.0f - 0.671877f,
		0.667969f, 1.0f - 0.671889f,
		1.000023f, 1.0f - 0.000013f,
		0.668104f, 1.0f - 0.000013f,
		0.667979f, 1.0f - 0.335851f,
		0.000059f, 1.0f - 0.000004f,
		0.335973f, 1.0f - 0.335903f,
		0.336098f, 1.0f - 0.000071f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.336024f, 1.0f - 0.671877f,
		1.000004f, 1.0f - 0.671847f,
		0.999958f, 1.0f - 0.336064f,
		0.667979f, 1.0f - 0.335851f,
		0.668104f, 1.0f - 0.000013f,
		0.335973f, 1.0f - 0.335903f,
		0.667979f, 1.0f - 0.335851f,
		0.335973f, 1.0f - 0.335903f,
		0.668104f, 1.0f - 0.000013f,
		0.336098f, 1.0f - 0.000071f,
		0.000103f, 1.0f - 0.336048f,
		0.000004f, 1.0f - 0.671870f,
		0.336024f, 1.0f - 0.671877f,
		0.000103f, 1.0f - 0.336048f,
		0.336024f, 1.0f - 0.671877f,
		0.335973f, 1.0f - 0.335903f,
		0.667969f, 1.0f - 0.671889f,
		1.000004f, 1.0f - 0.671847f,
		0.667979f, 1.0f - 0.335851f
	};

	VertexBuffer vb(g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
	VertexBuffer uvb(g_uv_buffer_data, sizeof(g_uv_buffer_data));

	basicShader.SetUniformMatrix4("MVP", MVP);

	Texture testTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/NumberedCube.bmp");
	testTexture.Bind(0);
	
	basicShader.SetUniformInt("textureSampler", 0);

	VertexBufferLayout vbLayout;
	vbLayout.PushFloat(3);

	VertexBufferLayout uvbLayout;
	uvbLayout.PushFloat(2);

	va.AddBuffer(&vb, vbLayout);
	va.AddBuffer(&uvb, uvbLayout);

	OBJReader reader;
	MeshData* tempData = reader.ReadFile("C:/Users/debgh/Documents/Meshes/airplane.obj");

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	LogRenderingError();

}

void Renderer::TempModelRenderer()
{
	OBJReader reader;
	MeshData* planeData = reader.ReadFile("C:/Users/debgh/Documents/Meshes/airplane.obj");

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	
	MeshComponent planeMesh(planeData, &basicShader);
	planeMesh.SetTransform(FTransform());
	planeMesh.transform.SetScale(FVector3(1.f, 1.f, 1.f));
	planeMesh.RecalculateModelMatrix();
	
	Texture testTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/NumberedCube.bmp");
	testTexture.Bind(0);
	basicShader.SetUniformInt("textureSampler", 0);

	FCameraData camera(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), 45.f);
	
	this->DrawMesh(planeMesh, camera);
}
