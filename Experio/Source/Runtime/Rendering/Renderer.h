#pragma once
#include "../../Engine.h"
#include <string>;
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shaders/Shader.h"
#include "Texture.h"
#include "Components/Billboard.h"
#include "Components/MeshComponent.h"
#include "FrameBuffer.h"
#include "../Math/FRect.h"

enum class ERenderMode
{
	ToCameraSystem,
	ToEditorSceneView,
	ToEditorGameView,
	ToEditorAssetView
};

class Renderer
{
private:
	VertexBufferLayout defaultVertexLayout;

	static Renderer* current;
	Shader* billboardShader;

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix();

	void SetupShaders();
public:
	ERenderMode currentMode = ERenderMode::ToCameraSystem;

	void LogRenderingError();

	Renderer();
	~Renderer();

	void MakeCurrent();

	void Clear();

	void ClearColor(FColor color);

	void OnNewFrame();
	void OnEndFrame();

	void DrawBillboard(const Billboard& billboard);

	void DrawMesh(const MeshComponent& mesh);

	void DrawQuad(unsigned int textureID, const Shader& shader, const FRect& uvRect, const FRect& vertexRect);
	void DrawQuad(const Texture& texture, const Shader& shader, const FRect& uvRect, const FRect& vertexRect);

	void SetCull(bool culling);
	void SetDepthTesting(bool depthTesting);
	void SetDither(bool dither);
	void SetViewport(int x, int y, unsigned int width, unsigned int height);

	void TempRenderer();

	void TempModelRenderer();

	void TempPostProcessingRenderer(Framebuffer& fb);

	void TempFramebufferRenderer();

	static Renderer* Get();
};