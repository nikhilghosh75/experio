#include "UniformBuffer.h"
#include <stdlib.h>
#include <string.h>

UniformBuffer::UniformBuffer()
{
	this->rendererID = UNIFORM_BUFFER_NOT_DEFINED;
}

UniformBuffer::UniformBuffer(void * data, unsigned int size)
{
	this->data = (void*)malloc(size);
	memcpy(this->data, data, size);
	this->size = size;
	glGenBuffers(1, &rendererID);
	glBindBuffer(GL_UNIFORM_BUFFER, rendererID);
	glBufferData(GL_UNIFORM_BUFFER, this->size, this->data, GL_STATIC_DRAW);
}

UniformBuffer::~UniformBuffer()
{
	delete this->data;
	glDeleteBuffers(1, &rendererID);
}

void UniformBuffer::Bind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, rendererID);
}

void UniformBuffer::Unbind() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBuffer::SetData(void * data, unsigned int size)
{
	delete this->data;

	this->data = (void*)malloc(size);
	memcpy(this->data, data, size);
	this->size = size;

	if (this->rendererID == UNIFORM_BUFFER_NOT_DEFINED)
	{
		glGenBuffers(1, &rendererID);
	}

	glBindBuffer(GL_UNIFORM_BUFFER, rendererID);
	glBufferData(GL_UNIFORM_BUFFER, size, this->data, GL_STATIC_DRAW);
}
