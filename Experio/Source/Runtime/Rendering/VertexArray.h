#pragma once
#include "VertexBuffer.h";
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int rendererID;
	unsigned int bufferCount;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer* buffer, const VertexBufferLayout& layout);
	void AddBuffer(const VertexBuffer* buffer, const VertexBufferLayout& layout, int attribDivisor);

	void Bind() const;
	void Unbind() const;

	void DestroyLayouts();
};