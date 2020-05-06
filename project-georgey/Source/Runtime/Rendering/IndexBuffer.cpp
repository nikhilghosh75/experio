#include "IndexBuffer.h"
#include <GL/glew.h>
#include <GL/GL.h>
#include <stdlib.h>
#include <string.h>

IndexBuffer::IndexBuffer()
{
	this->rendererID = 4294967294;
	this->count = 0;
}

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count)
{
	this->data = (void*)malloc(count * sizeof(unsigned int));
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
