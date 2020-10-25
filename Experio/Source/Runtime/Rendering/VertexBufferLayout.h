#pragma once
#include <vector>
#include "GL/glew.h"
#include "OpenGL/LOpenGL.h"

struct FVertexBufferElement
{
	int count;
	unsigned int type;
	bool isNormalized;

	FVertexBufferElement(int newCount, unsigned int newType, bool normalized)
	{
		count = newCount;
		type = newType;
		isNormalized = normalized;
	}

	size_t GetSize() const
	{
		return count * LOpenGL::GetSizeOfType(type);
	}
};

class VertexBufferLayout
{
private:
	std::vector<FVertexBufferElement> elements;
	unsigned int stride;

public:
	VertexBufferLayout();

	void PushFloat(int count);
	void PushUnsignedInt(int count);
	void PushUnsignedChar(int count);

	unsigned int GetStride() const;
	std::vector<FVertexBufferElement> GetElements() const;
};
