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
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

	//glClear(GL_COLOR_BUFFER_BIT);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableVertexAttribArray(0);
}
