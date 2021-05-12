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
#include "Blend.h"
#include "../Math/FRect.h"

enum class ERenderMode
{
	ToCameraSystem,
	ToEditorSceneView,
	ToEditorGameView,
	ToEditorAssetView
};

enum class EDrawCallType
{
	None,
	Mesh,
	Billboard,
	Quad
};

struct RendererStats
{
	unsigned int drawCalls = 0;
	unsigned int meshesRendered = 0;
	unsigned int billboardsRendered = 0;
	unsigned int quadsRendered = 0;
	unsigned int vertices;
};

class Renderer
{
public:
	VertexBufferLayout defaultVertexLayout;

	static Renderer* current;

	static Shader* billboardShader;
	static Shader* defaultQuadShader;
	static Shader* textShader;
	static Shader* progressBarShader;

private:

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix();

	void SetupShaders();

	void OnDrawCall(EDrawCallType type, unsigned int vertices);

	static RendererStats lastFrameStats;
	static RendererStats currentFrameStats;

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

	void DrawQuad(unsigned int textureID, const Shader* shader, const FRect& uvRect, const FRect& vertexRect);
	void DrawQuad(const Texture& texture, const Shader* shader, const FRect& uvRect, const FRect& vertexRect);

	void SetBlend(bool blend, EBlendFunc blendFunc = EBlendFunc::None);
	void SetCull(bool culling);
	void SetDepthTesting(bool depthTesting);
	void SetDither(bool dither);
	void SetViewport(int x, int y, unsigned int width, unsigned int height);

	void TempRenderer();

	void TempFramebufferRenderer();

	static Renderer* Get();
};