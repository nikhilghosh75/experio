#pragma once
#include "../../Engine.h"
#include <string>;
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "MeshData.h"
#include "FCameraData.h"

class Renderer
{
private:
	void LogRenderingError();
	VertexBufferLayout defaultVertexLayout;
public:
	Renderer();
	~Renderer();

	void Clear();

	void OnNewFrame();

	void DrawMesh(const FMeshData& mesh, const FCameraData& cameraData);

	void TempDraw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const;

	FMeshData* TempSetup();

	void TempRenderer();
};

