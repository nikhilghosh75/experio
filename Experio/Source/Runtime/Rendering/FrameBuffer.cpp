#include "Framebuffer.h"
#include "C:/Users/debgh/source/repos/project-bloo/Dependencies/GLEW/include/GL/glew.h"
#include "../Debug/Debug.h"

Framebuffer::Framebuffer()
{
	// Default Spec
	this->spec.width = 512;
	this->spec.height = 512;

	Build();
}

Framebuffer::Framebuffer(const FFramebufferSpec & spec)
{
	this->spec = spec;
	Build();
}

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
{
	this->spec.width = width;
	this->spec.height = height;
	Build();
}

Framebuffer::~Framebuffer()
{
	glDeleteRenderbuffers(1, &this->rendererID);
}

void Framebuffer::SetSpec(const FFramebufferSpec & spec)
{
	this->spec = spec;
	Build();
}

void Framebuffer::SetSpec(unsigned int width, unsigned int height)
{
	this->spec.width = width;
	this->spec.height = height;
	Build();
}

void Framebuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->rendererID);
}

void Framebuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::CheckFramebufferStatus()
{
	GLenum FramebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch (FramebufferStatus)
	{
	case GL_FRAMEBUFFER_UNDEFINED:
		Debug::LogError("Framebuffer undefined");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		Debug::LogError("Framebuffer attachment incompleted");
		break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		Debug::LogError("Framebuffer does not have anything attached");
		break;
	}
}

void Framebuffer::Build()
{
	glGenFramebuffers(1, &rendererID);
	glBindFramebuffer(GL_FRAMEBUFFER, rendererID);

	glGenTextures(1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, spec.width, spec.height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorAttachment, 0);

	glGenRenderbuffers(1, &depthAttachment);
	glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, spec.width, spec.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthAttachment);

	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	Unbind();
}
