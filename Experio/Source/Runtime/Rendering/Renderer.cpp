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
#include "../Core/Window.h"
#include "../Core/LWindowOperations.h"
#include <fstream>
#include "../Files/Images/ImageReader.h"
#include "../Files/Images/BMPReader.h"
#include "../Files/Images/TGAReader.h"
#include "../Files/Mesh/OBJReader.h"
#include "Texture.h"
#include "../Camera/VirtualCamera.h"

Renderer* Renderer::instance;

Shader* basicShader = nullptr;

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
	instance = this;
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

void Renderer::OnEndFrame()
{

}

void Renderer::DrawBillboard(const Billboard & billboard, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader billboardShader(
		"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/BillboardVertex.shader",
		"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/BillboardFragment.shader"
	);
	billboardShader.Bind();

	billboard.billboardTexture->Bind(0);
	billboardShader.SetUniformInt("albedoTexture", 0);

	static const float billboardBufferData[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f
	};

	VertexBuffer billboardBuffer(billboardBufferData, sizeof(billboardBufferData));

	FWindowData data = Window::GetWindowData();
	float aspectRatio = LWindowOperations::GetAspectRatio(data);

	glm::mat4 VP = projectionMatrix * viewMatrix;

	billboardShader.SetUniformVec3("cameraRightWorldSpace", glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
	billboardShader.SetUniformVec3("cameraUpWorldSpace", glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
	billboardShader.SetUniformVec3("billboardPosition", billboard.GetGameObject()->GetPosition());
	billboardShader.SetUniformVec2("billboardSize", billboard.billboardSize);
	billboardShader.SetUniformMatrix4("VP", VP);
	billboardShader.SetUniformInt("billboardSizeType", (int)billboard.sizeType);
	billboardShader.SetUniformInt("billboardOrientation", (int)billboard.orientation);

	VertexBufferLayout billboardLayout;
	billboardLayout.PushFloat(3);

	VertexArray billboardVA;
	billboardVA.AddBuffer(&billboardBuffer, billboardLayout);

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glDisable(GL_BLEND);
}

void Renderer::DrawMesh(const MeshComponent & mesh, const glm::mat4 viewMatrix, const glm::mat4 projectionMatrix)
{
	PROFILE_SCOPE("Rendering Mesh");

	if (!mesh.isVisible)
	{
		return;
	}

	glm::mat4 modelMatrix = mesh.GetModelMatrix();

	FWindowData data = Window::GetWindowData();
	float aspectRatio = LWindowOperations::GetAspectRatio(data);

	glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	glm::mat3 MV3x3 = glm::mat3(viewMatrix * modelMatrix);

	mesh.meshShader->Bind();
	mesh.meshShader->SetUniformMatrix4("MVP", MVP);
	mesh.meshShader->SetUniformMatrix4("M", modelMatrix);
	mesh.meshShader->SetUniformMatrix4("V", viewMatrix);
	mesh.meshShader->SetUniformMatrix3("MV3x3", MV3x3);

	VertexArray va;

	VertexBufferLayout positionLayout;
	positionLayout.PushFloat(3);
	VertexBufferLayout uvLayout;
	uvLayout.PushFloat(2);
	VertexBufferLayout normalLayout;
	normalLayout.PushFloat(3);
	VertexBufferLayout tangentLayout;
	tangentLayout.PushFloat(3);
	VertexBufferLayout bitangentLayout;
	bitangentLayout.PushFloat(3);

	va.AddBuffer(mesh.meshData->verticies, positionLayout);
	va.AddBuffer(mesh.meshData->uv, uvLayout);
	va.AddBuffer(mesh.meshData->normals, normalLayout);
	va.AddBuffer(mesh.meshData->tangents, tangentLayout);
	va.AddBuffer(mesh.meshData->bitangents, bitangentLayout);

	if (mesh.meshData->isIndexed)
	{
		mesh.meshData->indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, mesh.meshData->indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		return;
	}

	glDrawArrays(GL_TRIANGLES, 0, mesh.meshData->GetTriangleCount());
}

void Renderer::DrawQuad(unsigned int textureID, const Shader & shader, const FRect & uvRect, const FRect & vertexRect)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	shader.Bind();

	glm::vec2 verticies[6] = {
		vertexRect.GetTopLeft(), vertexRect.GetBottomLeft(), vertexRect.GetTopRight(),
		vertexRect.GetBottomRight(), vertexRect.GetTopRight(), vertexRect.GetBottomLeft()
	};

	glm::vec2 uvs[6] = {
		glm::vec2(uvRect.min.x + 0.03f, 1.f - uvRect.min.y), glm::vec2(uvRect.min.x + 0.03f, 1.f - uvRect.max.y), glm::vec2(uvRect.max.x + 0.03f, 1.f - uvRect.min.y),
		glm::vec2(uvRect.max.x + 0.03f, 1.f - uvRect.max.y), glm::vec2(uvRect.max.x + 0.03f, 1.f - uvRect.min.y), glm::vec2(uvRect.min.x + 0.03f, 1.f - uvRect.max.y)
	};

	VertexBuffer vertexBuffer(verticies, sizeof(verticies));
	VertexBuffer uvBuffer(uvs, sizeof(uvs));

	VertexArray va;

	VertexBufferLayout vertexLayout, uvLayout;
	vertexLayout.PushFloat(2);
	uvLayout.PushFloat(2);

	va.AddBuffer(&vertexBuffer, vertexLayout);
	va.AddBuffer(&uvBuffer, uvLayout);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::DrawQuad(const Texture & texture, const Shader & shader, const FRect & uvRect, const FRect & vertexRect)
{
	shader.Bind();
	texture.Bind();

	glm::vec2 verticies[6] = {
		vertexRect.GetTopLeft(), vertexRect.GetBottomLeft(), vertexRect.GetTopRight(),
		vertexRect.GetBottomRight(), vertexRect.GetTopRight(), vertexRect.GetBottomLeft()
	};
	
	glm::vec2 uvs[6] = {
		glm::vec2(uvRect.min.x + 0.03f, 1.f - uvRect.min.y), glm::vec2(uvRect.min.x + 0.03f, 1.f - uvRect.max.y), glm::vec2(uvRect.max.x + 0.03f, 1.f - uvRect.min.y),
		glm::vec2(uvRect.max.x + 0.03f, 1.f - uvRect.max.y), glm::vec2(uvRect.max.x + 0.03f, 1.f - uvRect.min.y), glm::vec2(uvRect.min.x + 0.03f, 1.f - uvRect.max.y)
	};

	VertexBuffer vertexBuffer(verticies, sizeof(verticies));
	VertexBuffer uvBuffer(uvs, sizeof(uvs));
	
	VertexArray va;

	VertexBufferLayout vertexLayout, uvLayout;
	vertexLayout.PushFloat(2);
	uvLayout.PushFloat(2);

	va.AddBuffer(&vertexBuffer, vertexLayout);
	va.AddBuffer(&uvBuffer, uvLayout);

	glDrawArrays(GL_TRIANGLES, 0, 6);
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
	LogRenderingError();

	PROFILE_SCOPE("Rendering");

	BMPReader bmpReader;

	Clear();

	// REGULAR

	Shader basicShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/BasicFragment.shader");
	basicShader.Bind();

	Shader textShader("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DVertex.shader", "C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/Text2DFragment.shader");

	glm::vec3 lightPosition = glm::vec3(4, 4, 4);
	basicShader.SetUniformVec3("LightWorldPosition", lightPosition);

	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	basicShader.SetUniformVec3("LightColor", lightColor);

	float lightIntensity = 50.0f;
	basicShader.SetUniformFloat("LightPower", lightIntensity);

	Texture albedoTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/uvmap.bmp");
	albedoTexture.Bind(0);
	basicShader.SetUniformInt("albedoTexture", 0);

	//Texture normalTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/normal.bmp");
	//normalTexture.Bind(1);
	//basicShader.SetUniformInt("normalTexture", 1);

	//Texture specularTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/specular.bmp");
	//specularTexture.Bind(2);
	//basicShader.SetUniformInt("specularTexture", 2);

	OBJReader objReader;
	MeshData* tempData = objReader.ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Meshes/suzanne.obj");
	// MeshData* tempData = objReader.ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Meshes/cylinder.obj");
	tempData->mapData = new MeshMapData();
	tempData->mapData->albedoMap = &albedoTexture;
	//tempData->mapData->normalMap = &normalTexture;
	//tempData->mapData->specularMap = &specularTexture;

	// MeshComponent suzanneMesh(tempData, &basicShader);
	GameObject tempObject;
	MeshComponent suzanneMesh(&tempObject);
	suzanneMesh.meshData = tempData;
	suzanneMesh.meshShader = &basicShader;
	suzanneMesh.GetGameObject()->localRotation = FQuaternion::MakeFromEuler(FVector3(0, 90, 0));
	suzanneMesh.GetGameObject()->localScale = FVector3(0.7, 0.7, 0.7);
	suzanneMesh.RecalculateModelMatrix();

	//glm::mat4 viewMatrix = (FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), 45.f);
	glm::mat4 viewMatrix = VirtualCamera::CalculateViewMatrix(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))));
	glm::mat4 projectionMatrix = VirtualCamera::CalculateProjectionMatrix(45.f, 0.1f, 1000.f);

	this->DrawMesh(suzanneMesh, viewMatrix, projectionMatrix);

	// BILLBOARDS

	//Texture healthbarTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/HealthBar.bmp");
	//Billboard billboard(nullptr);
	//billboard.sizeType = EBillboardSizeType::World;
	//billboard.billboardTexture = &healthbarTexture;
	//billboard.billboardPosition = FVector3(0, 2, 0);
	//billboard.billboardSize = FVector2(1.0f, 0.125f);
	//billboard.orientation = EBilboardOrientation::TowardCamera;

	//this->DrawBillboard(billboard, camera);
	
	LogRenderingError();

	delete tempData;
}

void Renderer::TempFramebufferRenderer()
{
	LogRenderingError();

	PROFILE_SCOPE("Rendering Framebuffer");

	FWindowData windowData = Window::GetWindowData();

	glEnable(GL_CULL_FACE);

	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowData.width, windowData.height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTexture, 0);

	GLuint rboDepthStencil;
	glGenRenderbuffers(1, &rboDepthStencil);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepthStencil);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboDepthStencil);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	unsigned int framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE)
	{
		GDebug::LogError("Framebuffer Object");
		return;
	}

	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		-1.0f,  1.0f,
		-1.0f,  1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
	};

	static const GLfloat g_quad_uv_buffer_data[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};
	glViewport(0, 0, windowData.width, windowData.height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// REGULAR

	GLuint buffer;
	float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);

	// FRAMBUFFER
	glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, windowData.width, windowData.height);

	Clear();

	Shader quadShader(
		"C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/FullScreenVertex.shader",
		"C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Shaders/FullScreenFragment.shader"
	);
	quadShader.Bind();
	quadShader.SetUniformInt("textureSampler", 3);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	VertexBuffer vertexBuffer(g_quad_vertex_buffer_data, sizeof(g_quad_vertex_buffer_data));
	VertexBuffer uvBuffer(g_quad_uv_buffer_data, sizeof(g_quad_uv_buffer_data));

	VertexBufferLayout quadLayout;
	quadLayout.PushFloat(2);

	VertexArray va;
	va.AddBuffer(&vertexBuffer, quadLayout);
	va.AddBuffer(&uvBuffer, quadLayout);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
