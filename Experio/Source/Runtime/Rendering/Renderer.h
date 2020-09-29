#pragma once
#include "../../Engine.h"
#include <string>;
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Billboard.h"
#include "MeshComponent.h"
#include "FrameBuffer.h"
#include "../Math/FRect.h"

enum class ERenderMode
{
	ToCameraSystem,
	ToEditorSceneView,
	ToEditorGameView
};

class Renderer
{
private:
	VertexBufferLayout defaultVertexLayout;

	static Renderer* current;

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix();
public:
	ERenderMode currentMode = ERenderMode::ToCameraSystem;

	void LogRenderingError();

	Renderer();
	~Renderer();

	void MakeCurrent();

	void Clear();

	void OnNewFrame();
	void OnEndFrame();

	void DrawBillboard(const Billboard& billboard);

	void DrawMesh(const MeshComponent& mesh);

	void DrawQuad(unsigned int textureID, const Shader& shader, const FRect& uvRect, const FRect& vertexRect);
	void DrawQuad(const Texture& texture, const Shader& shader, const FRect& uvRect, const FRect& vertexRect);

	void TempDraw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
	void TempDraw(const VertexArray* va, const Shader* shader, int count) const;

	void TempRenderer();

	void TempModelRenderer();

	void TempPostProcessingRenderer(Framebuffer& fb);

	void TempFramebufferRenderer();

	static Renderer* Get();
};