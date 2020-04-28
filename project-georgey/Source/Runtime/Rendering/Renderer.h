#pragma once
#include "../../Engine.h"
#include <string>;
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "MeshData.h"

class Renderer
{
private:
	void LogRenderingError();
public:
	Renderer();
	~Renderer();

	void Clear();

	void OnNewFrame();

	void DrawMesh(const FMeshData& mesh);

	void TempDraw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	void TempRenderer();
};

