#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GL/GL.h>
#include <stdlib.h>
#include <string.h>
#include "LOpenGL.h"
#include "../Data/NumericData.h"

VertexBuffer::VertexBuffer()
{
	this->rendererID = VERTEX_BUFFER_NOT_DEFINED;
}

VertexBuffer::VertexBuffer(NumericData & data)
{
	this->size = data.Size();
	this->dataType = data.GetDataType();
	this->data = (void*)malloc(this->size);
	memcpy(this->data, data.GetData(), this->size);
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, this->size, this->data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	this->data = (void*) malloc(size);
	memcpy(this->data, data, size);
	this->size = size;
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, this->data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void * data, unsigned int size, unsigned int dataType)
{
	this->data = (void*)malloc(size);
	memcpy(this->data, data, size);
	this->size = size;
	this->dataType = (EDataType)dataType;

	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, this->data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void * data, unsigned int size, EDataType dataType)
{
	this->data = (void*)malloc(size);
	memcpy(this->data, data, size);
	this->size = size;
	this->dataType = (EDataType)dataType;

	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, this->data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	delete this->data;
	glDeleteBuffers(1, &rendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void * data, unsigned int size)
{
	delete this->data;

	this->data = (void*)malloc(size);
	memcpy(this->data, data, size);
	this->size = size;
	
	if (this->rendererID == VERTEX_BUFFER_NOT_DEFINED)
	{
		glGenBuffers(1, &rendererID);
	}

	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, this->data, GL_STATIC_DRAW);
}

void VertexBuffer::SetData(const void * data, unsigned int size, EDataType dataType)
{
	this->data = (void*)malloc(size);
	memcpy(this->data, data, size);
	this->size = size;
	this->dataType = dataType;

	if (this->rendererID == VERTEX_BUFFER_NOT_DEFINED)
	{
		glGenBuffers(1, &rendererID);
	}

	glBindBuffer(GL_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, this->data, GL_STATIC_DRAW);
}

unsigned int VertexBuffer::GetCount() const
{
	return this->size / LOpenGL::GetSizeOfType(dataType);
}

GLfloat * VertexBuffer::GetDataAsFloatArray() const
{
	return (GLfloat*)this->data;
}

GLint * VertexBuffer::GetDataAsIntArray() const
{
	return (GLint*)this->data;
}
