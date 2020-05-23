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
	mesh.meshShader->SetUniformMatrix4("M", modelMatrix);
	mesh.meshShader->SetUniformMatrix4("V", viewMatrix);

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

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	basicShader.Bind();

	glm::vec3 lightPosition = glm::vec3(4, 4, 4);
	basicShader.SetUniformVec3("LightWorldPosition", lightPosition);

	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	basicShader.SetUniformVec3("LightColor", lightColor);

	float lightIntensity = 50.0f;
	basicShader.SetUniformFloat("LightPower", lightIntensity);

	Texture testTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/uvmap.bmp");
	testTexture.Bind(0);
	basicShader.SetUniformInt("textureSampler", 0);

	OBJReader objReader;
	MeshData* tempData = objReader.ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Meshes/suzanne.obj");

	MeshComponent suzanneMesh(tempData, &basicShader);
	suzanneMesh.SetTransform(FTransform());
	suzanneMesh.transform.SetRotation(FQuaternion::MakeFromEuler(FVector3(0, 90, 0)));
	suzanneMesh.transform.SetScale(FVector3(1, 1, 1));
	suzanneMesh.RecalculateModelMatrix();

	FCameraData camera(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), 45.f);

	this->DrawMesh(suzanneMesh, camera);

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
