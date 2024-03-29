#include "VertexArray.h"
#include "../Debug/Debug.h"

VertexArray::VertexArray()
{
	rendererID = 0;
	bufferCount = 0;
	glGenVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer* buffer, const VertexBufferLayout & layout)
{
	if (buffer == nullptr)
	{
		Debug::LogError("Attempted to add null buffer to Vertex Array " + std::to_string(rendererID));
		return;
	}

	const std::vector<FVertexBufferElement> elements = layout.GetElements();
	Bind();
	buffer->Bind();
	unsigned int offset = 0;
	glEnableVertexAttribArray(bufferCount);
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		FVertexBufferElement element = elements[i];
		glVertexAttribPointer(bufferCount, element.count, element.type, (GLboolean)element.isNormalized, layout.GetStride(), (const void*)offset);
		offset += element.GetSize();
	}
	bufferCount++;
}

void VertexArray::AddBuffer(const VertexBuffer* buffer, const VertexBufferLayout& layout, int attribDivisor)
{
	AddBuffer(buffer, layout);
	glVertexAttribDivisor(bufferCount - 1, attribDivisor);
}

void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::DestroyLayouts()
{
	for (int i = 0; i < bufferCount; i++)
	{
		glDisableVertexAttribArray(i);
	}
	bufferCount = 0;
}
