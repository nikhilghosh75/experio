#include "../Core/Core.h"
#include "Renderer.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "../Math/LMath.h"
#include "../Debug/Debug.h"
#include "../Debug/Profiler.h"
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
#include "FrameBuffer.h"
#include "../Framework/Project.h"
#include "../Camera/CameraSystem.h"
#include "../Camera/AdditionalCameras.h"
#include "Managers/TextureManager.h"
#include "Shaders/ShaderReader.h"

Renderer* Renderer::current;

Shader* basicShader = nullptr;
Shader* Renderer::billboardShader;
Shader* Renderer::defaultQuadShader;
Shader* Renderer::textShader;

RendererStats Renderer::lastFrameStats;
RendererStats Renderer::currentFrameStats;

Renderer::Renderer()
{
	SetupShaders();
	defaultVertexLayout.PushFloat(3);
}

Renderer::~Renderer()
{
	delete billboardShader;
}

glm::mat4 Renderer::GetViewMatrix()
{
	switch (currentMode)
	{
	case ERenderMode::ToCameraSystem:
		return CameraSystem::Get()->currentViewMatrix;
	case ERenderMode::ToEditorSceneView:
		return AdditionalCameras::viewMatrix;
	case ERenderMode::ToEditorAssetView:
		return AdditionalCameras::viewMatrix;
	}
	return glm::mat4();
}

glm::mat4 Renderer::GetProjectionMatrix()
{
	switch (currentMode)
	{
	case ERenderMode::ToCameraSystem:
		return CameraSystem::Get()->currentProjectionMatrix;
	case ERenderMode::ToEditorSceneView:
		return AdditionalCameras::projectionMatrix;
	case ERenderMode::ToEditorAssetView:
		return AdditionalCameras::projectionMatrix;
	}
	return glm::mat4();
}

void Renderer::SetupShaders()
{
	std::string standardShadersPath = "";
	if (Project::inEditor)
	{
		standardShadersPath = Project::experioResourcesPath + "/Standard/Shaders";
	}

	billboardShader = ShaderReader::ReadShader(standardShadersPath + "/Billboard.shader");
	defaultQuadShader = ShaderReader::ReadShader(standardShadersPath + "/Quad.shader");
	textShader = ShaderReader::ReadShader(standardShadersPath + "/Text2D.shader");
}

void Renderer::LogRenderingError()
{
	GLenum currentError = glGetError();
	if (currentError != GL_NO_ERROR)
	{
		Debug::LogError("OPENGL Error " + std::to_string(currentError));
	}
}

void Renderer::MakeCurrent()
{
	current = this;
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearColor(FColor color)
{
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::OnNewFrame()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::OnEndFrame()
{

}

void Renderer::OnDrawCall(EDrawCallType type, unsigned int vertices)
{
	currentFrameStats.drawCalls++;
	currentFrameStats.vertices += vertices;
	
	switch (type)
	{
	case EDrawCallType::Billboard: currentFrameStats.billboardsRendered++; break;
	case EDrawCallType::Mesh: currentFrameStats.meshesRendered++; break;
	case EDrawCallType::Quad: currentFrameStats.quadsRendered++; break;
	}
}

void Renderer::DrawBillboard(const Billboard & billboard)
{
	glm::mat4 projectionMatrix = GetProjectionMatrix();
	glm::mat4 viewMatrix = GetViewMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	billboardShader->Bind();

	billboard.billboardTexture->Bind(0);
	billboardShader->SetUniformInt("albedoTexture", 0);

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

	billboardShader->SetUniformVec3("cameraRightWorldSpace", glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]));
	billboardShader->SetUniformVec3("cameraUpWorldSpace", glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]));
	billboardShader->SetUniformVec3("billboardPosition", billboard.GetGameObject()->GetPosition());
	billboardShader->SetUniformVec2("billboardSize", billboard.billboardSize);
	billboardShader->SetUniformMatrix4("VP", VP);
	billboardShader->SetUniformInt("billboardSizeType", (int)billboard.sizeType);
	billboardShader->SetUniformInt("billboardOrientation", (int)billboard.orientation);

	VertexBufferLayout billboardLayout;
	billboardLayout.PushFloat(3);

	VertexArray billboardVA;
	billboardVA.AddBuffer(&billboardBuffer, billboardLayout);

	glDrawArrays(GL_TRIANGLES, 0, 12);
	OnDrawCall(EDrawCallType::Billboard, 12);

	glDisable(GL_BLEND);
}

void Renderer::DrawMesh(const MeshComponent & mesh)
{
	PROFILE_SCOPE("Renderer::DrawMesh");

	if (!mesh.isVisible)
	{
		return;
	}

	glm::mat4 projectionMatrix = GetProjectionMatrix();
	glm::mat4 viewMatrix = GetViewMatrix();

	glm::mat4 modelMatrix = mesh.GetModelMatrix();

	mesh.material->Bind();
	mesh.material->SetInternalUniforms();
	mesh.material->SetLightingData(FLightData(FVector3(4, 4, 4), FQuaternion(), FColor(1, 1, 1), 20.f));
	mesh.material->SetMVP(modelMatrix, viewMatrix, projectionMatrix);

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

	mesh.material->SetInternalBuffers(va);

	if (mesh.meshData->isIndexed)
	{
		mesh.meshData->indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, mesh.meshData->indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		currentFrameStats.drawCalls++;
		currentFrameStats.meshesRendered++;
		currentFrameStats.vertices += mesh.meshData->GetTriangleCount();
		return;
	}

	glDrawArrays(GL_TRIANGLES, 0, mesh.meshData->GetTriangleCount());
	OnDrawCall(EDrawCallType::Mesh, mesh.meshData->GetTriangleCount());
}

void Renderer::DrawQuad(unsigned int textureID, const Shader* shader, const FRect & uvRect, const FRect & vertexRect)
{
	if (shader == nullptr)
	{
		shader = defaultQuadShader;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	shader->Bind();

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
	OnDrawCall(EDrawCallType::Quad, 6);
}

void Renderer::DrawQuad(const Texture & texture, const Shader* shader, const FRect & uvRect, const FRect & vertexRect)
{
	if (shader == nullptr)
	{
		shader = defaultQuadShader;
	}

	shader->Bind();
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
	OnDrawCall(EDrawCallType::Quad, 6);
}

void Renderer::SetBlend(bool blend, EBlendFunc blendFunc)
{
	if (blend)
	{
		glEnable(GL_BLEND);
		GLenum func = LOpenGL::GetBlendFunc(blendFunc);
		glBlendFunc(GL_SRC_ALPHA, func);
	}
	else
		glDisable(GL_BLEND);
}

void Renderer::SetCull(bool culling)
{
	if (culling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void Renderer::SetDepthTesting(bool depthTesting)
{
	if (depthTesting)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Renderer::SetDither(bool dither)
{
	if (dither)
		glEnable(GL_DITHER);
	else
		glDisable(GL_DITHER);
}

void Renderer::SetViewport(int x, int y, unsigned int width, unsigned int height)
{
	glViewport(x, y, width, height);
}

void Renderer::TempRenderer()
{
	LogRenderingError();

	PROFILE_SCOPE("Rendering");

	BMPReader bmpReader;

	Clear();

	OBJReader objReader;
	// MeshData* tempData = objReader.ReadFile("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Meshes/suzanne.obj");

	// MeshComponent suzanneMesh(tempData, &basicShader);
	GameObject tempObject;
	MeshComponent suzanneMesh(&tempObject);
	suzanneMesh.meshData = MeshManager::LoadMesh("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Meshes/suzanne.obj");
	suzanneMesh.material = new MeshMaterial();
	suzanneMesh.material->SetShader("C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/Basic.shader");
	suzanneMesh.material->albedo = TextureManager::LoadTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/uvmap.bmp");
	suzanneMesh.material->normal = TextureManager::LoadTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/normal.bmp");
	suzanneMesh.material->specular = TextureManager::LoadTexture("C:/Users/debgh/source/repos/project-bloo/project-georgey/Resources/Standard/Textures/specular.bmp");
	suzanneMesh.GetGameObject()->localRotation = FQuaternion::MakeFromEuler(FVector3(0, 90, 0));
	suzanneMesh.GetGameObject()->localScale = FVector3(0.7, 0.7, 0.7);
	suzanneMesh.RecalculateModelMatrix();

	//glm::mat4 viewMatrix = (FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))), 45.f);
	glm::mat4 viewMatrix = VirtualCamera::CalculateViewMatrix(FVector3(4.f, 3.f, -3.f), FQuaternion(glm::lookAt(glm::vec3(4, 3, -3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))));
	glm::mat4 projectionMatrix = VirtualCamera::CalculateProjectionMatrix(45.f, 0.1f, 1000.f);

	this->DrawMesh(suzanneMesh);

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
}

void Renderer::TempFramebufferRenderer()
{
	FWindowData window = Window::GetWindowData();

	VertexBufferLayout layout;
	layout.PushFloat(2);

	Framebuffer framebuffer(window.width, window.height);
	framebuffer.Bind();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	unsigned int framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	framebuffer.CheckFramebufferStatus();

	Project::componentManager->Update();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Render on the whole framebuffer, complete from the lower left corner to the upper right
	glViewport(0, 0, window.width, window.height);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use our shader
	Shader* framebufferShader = ShaderReader::ReadShader(
		"C:/Users/debgh/source/repos/project-bloo/Experio/Resources/Standard/Shaders/InvertedScreen.shader"
	);
	framebufferShader->Bind();

	framebuffer.Unbind();

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, framebuffer.GetColorAttachment());
	
	framebufferShader->SetUniformInt("textureSampler", 0);

	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		-1.0f,  1.0f,
		-1.0f,  1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
	};

	unsigned int quadVertexBuffer;
	glGenBuffers(1, &quadVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quadVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Draw the triangles !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

	glDisableVertexAttribArray(0);
}

Renderer* Renderer::Get()
{
	if (current == nullptr)
	{
		Debug::LogError("Current Renderer is null");
	}
	return Renderer::current;
}