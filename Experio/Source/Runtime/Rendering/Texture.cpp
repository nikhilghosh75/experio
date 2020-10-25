#include "Texture.h"
#include "../Files/Images/BMPReader.h"
#include "../Files/Images/LImageOperations.h"
#include "OpenGL/LOpenGL.h"
#include "GL/glew.h"
#include "../Debug/Debug.h"

Texture::Texture()
{
	data = nullptr;
	glGenTextures(1, &this->rendererID);
}

Texture::Texture(const char * fileName)
{
	// TO-DO: Add more stuff as more image readers get made.

	BMPReader reader;
	this->data = ImageReader::ReadFile(fileName);

	glGenTextures(1, &this->rendererID);
	ConfigureData();
}

Texture::Texture(ImageData * data)
{
	this->data = data;

	glGenTextures(1, &this->rendererID);
	ConfigureData();
}

Texture::~Texture()
{
	delete this->data;
}

void Texture::ConfigureData()
{
	if (this->data == nullptr)
	{
		Debug::LogError("The data could not be loaded");
		return;
	}
	GLenum internalFormat = LOpenGL::GetInternalFormat(this->data->encoding, this->data->fileType);
	GLenum imageFormat = LOpenGL::GetImageFormat(this->data->encoding, this->data->fileType);

	glBindTexture(GL_TEXTURE_2D, this->rendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, this->data->width, this->data->height, 0, imageFormat, GL_UNSIGNED_BYTE, this->data->data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::SetData(ImageData * data)
{
	this->data = data;
	ConfigureData();
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->rendererID);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}