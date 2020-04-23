#include "VertexArray.h"

VertexArray::VertexArray()
{
	rendererID = 0;
	glGenVertexArrays(1, &rendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer & buffer, const VertexBufferLayout & layout)
{
	const std::vector<FVertexBufferElement> elements = layout.GetElements();
	Bind();
	buffer.Bind();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		FVertexBufferElement element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, (GLboolean)element.isNormalized, layout.GetStride(), (const void*)offset);
		offset += element.count;
	}

	GLboolean testBool = GL_TRUE;
}

void VertexArray::Bind() const
{
	glBindVertexArray(rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
