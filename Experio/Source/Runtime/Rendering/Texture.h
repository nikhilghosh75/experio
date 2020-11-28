#pragma once
#include "../Files/Images/ImageReader.h"

class Texture
{
private:
	ImageData* data;
	unsigned int rendererID;

	void ConfigureData();

public:
	Texture();
	Texture(const char* fileName);
	Texture(ImageData* data);

	~Texture();

	void SetData(ImageData* data);
	void SetData(void* data, int width, int height, EImageEncoding encoding, bool invertedPixels = false);

	void Bind(unsigned int slot = 0) const;
	void UnBind() const;

	unsigned int GetRendererID() const;

	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	EImageEncoding GetImageEncoding() const;
};