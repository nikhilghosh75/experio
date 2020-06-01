#pragma once
#include "../../Engine.h"
#include <string>;
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "MeshComponent.h"
#include "../Math/FRect.h"
#include "../Camera/FCameraData.h"

class Renderer
{
private:
	VertexBufferLayout defaultVertexLayout;
public:
	void LogRenderingError();

	Renderer();
	~Renderer();

	void Clear();

	void OnNewFrame();

	void DrawMesh(const MeshComponent& mesh, const FCameraData& cameraData);

	void DrawQuad(const Texture& texture, const Shader& shader, const FRect& uvRect, const FRect& vertexRect);

	void TempDraw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;
	void TempDraw(const VertexArray* va, const Shader* shader, int count) const;

	void TempRenderer();

	void TempModelRenderer();
};

