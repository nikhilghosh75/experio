#pragma once
#include "GL/glew.h"

#define VERTEX_BUFFER_NOT_DEFINED 4294967294

enum class EDataType
{
	NONE = 0,
	BYTE = 5120,
	UNSIGNED_BYTE = 5121,
	SHORT = 5122,
	UNSIGNED_SHORT = 5123,
	INT = 5124,
	UNSIGNED_INT = 5125,
	FLOAT = 5126,
	DOUBLE = 5130,
	HALF_FLOAT = 5131,
	FIXED = 5132
};

class NumericData;

class VertexBuffer
{
private:
	unsigned int rendererID;
	void* data;
	unsigned int size; // in bytes
	EDataType dataType;

public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer(NumericData& data);
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const void* data, unsigned int size, unsigned int dataType);
	VertexBuffer(const void* data, unsigned int size, EDataType dataType);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetData(const void* data, unsigned int size);
	void SetData(const void* data, unsigned int size, EDataType dataType);

	VertexBuffer operator=(const VertexBuffer&) = delete;

	unsigned int GetSize() const { return this->size; }
	unsigned int GetCount() const;
	void* GetData() const { return this->data; }
	EDataType GetDataType() const { return this->dataType; }

	GLfloat* GetDataAsFloatArray() const;
	GLint* GetDataAsIntArray() const;
};