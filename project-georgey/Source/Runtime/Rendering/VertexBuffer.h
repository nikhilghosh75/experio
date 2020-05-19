#pragma once

class VertexBuffer
{
private:
	unsigned int rendererID;
	void* data;
	unsigned int size;

public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	VertexBuffer operator=(const VertexBuffer&) = delete;

	unsigned int GetSize() const { return this->size; }
};