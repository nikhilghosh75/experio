#pragma once
#include "GL/glew.h"

#define UNIFORM_BUFFER_NOT_DEFINED 4294967295

class UniformBuffer
{
	unsigned int rendererID;
	void* data;
	unsigned int size;

public:
	UniformBuffer();
	UniformBuffer(void* data, unsigned int size);

	~UniformBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(void* data, unsigned int size);

	UniformBuffer operator=(const UniformBuffer&) = delete;

	unsigned int GetSize() const { return this->size; }
	void* GetData() const { return this->data; }
};