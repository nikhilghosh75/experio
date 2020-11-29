#include "IndexBuffer.h"
#include <GL/glew.h>
#include <GL/GL.h>
#include <stdlib.h>
#include <string.h>

#define NO_RENDERER_ID 4294967294

IndexBuffer::IndexBuffer()
{
	this->rendererID = NO_RENDERER_ID;
	this->count = 0;
	this->data = nullptr;
}

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count)
{
	this->data = (unsigned int*)malloc(count * sizeof(unsigned int));
	memcpy(this->data, data, count * sizeof(unsigned int));
	this->count = count;
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), this->data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	delete this->data;
	glDeleteBuffers(1, &rendererID);
}

void IndexBuffer::SetData(unsigned int * data, unsigned int count)
{
	this->data = (unsigned int*)malloc(count * sizeof(unsigned int));
	memcpy(this->data, data, count * sizeof(unsigned int));
	this->count = count;
	if (this->rendererID == NO_RENDERER_ID)
	{
		glGenBuffers(1, &rendererID);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), this->data, GL_STATIC_DRAW);
}

void IndexBuffer::MoveData(unsigned int * data, unsigned int count)
{
	this->data = data;
	this->count = count;
	if (this->rendererID == NO_RENDERER_ID)
	{
		glGenBuffers(1, &rendererID);
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), this->data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetCount() const
{
	return this->count;
}

unsigned int IndexBuffer::GetSize() const
{
	return this->count * sizeof(unsigned int);
}

unsigned int* IndexBuffer::GetData() const
{
	return this->data;
}
