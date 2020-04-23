#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
	stride = 0;
}

void VertexBufferLayout::PushFloat(int count)
{
	elements.emplace_back(count, GL_FLOAT, false);
	stride += GetSizeOfType(GL_FLOAT) * count;
}

void VertexBufferLayout::PushUnsignedInt(int count)
{
	elements.emplace_back(count, GL_UNSIGNED_INT, false); 
	stride += GetSizeOfType(GL_UNSIGNED_INT) * count;
}

void VertexBufferLayout::PushUnsignedChar(int count)
{
	elements.emplace_back(count, GL_UNSIGNED_BYTE, false);
	stride += GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}

unsigned int VertexBufferLayout::GetStride() const
{
	return 0;
}

std::vector<FVertexBufferElement> VertexBufferLayout::GetElements() const
{
	return elements;
}

size_t VertexBufferLayout::GetSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
		return 1;
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
	case GL_HALF_FLOAT:
		return 2;
	case GL_FLOAT:
	case GL_INT:
	case GL_UNSIGNED_INT:
	case GL_FIXED:
		return 4;
	case GL_DOUBLE:
		return 8;
	}
	return 0;
}
