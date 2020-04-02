#include "../Core/Core.h"
#include "Renderer.h"
#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include "../Debug/GDebug.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::TempRenderer()
{
	GLuint buffer;
	float positions[6] = { -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f };
	GDebug::Log("Positions");
	glGenBuffers(1, &buffer);
	GDebug::Log("Generate Buffers");
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	GDebug::Log("Bind Buffers");
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	GDebug::Log("Buffer Data");

	//glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	GDebug::Log("EnableVertexAtribArray");
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	GDebug::Log("Vertex Attrib Pointer");
	glDrawArrays(GL_TRIANGLES, 0, 3);
	GDebug::Log("Draw Arrays");
	glDisableVertexAttribArray(0);
	GDebug::Log("Disable Vertex Attrib Array");
}
