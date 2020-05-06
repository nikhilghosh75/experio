#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
	stride = 0;
}

void VertexBufferLayout::PushFloat(int count)
{
	elements.emplace_back(count, GL_FLOAT, false);
	stride += LOpenGL::GetSizeOfType(GL_FLOAT) * count;
}

void VertexBufferLayout::PushUnsignedInt(int count)
{
	elements.emplace_back(count, GL_UNSIGNED_INT, false); 
	stride += LOpenGL::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

void VertexBufferLayout::PushUnsignedChar(int count)
{
	elements.emplace_back(count, GL_UNSIGNED_BYTE, false);
	stride += LOpenGL::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}

unsigned int VertexBufferLayout::GetStride() const
{
	return stride;
}

std::vector<FVertexBufferElement> VertexBufferLayout::GetElements() const
{
	return elements;
}