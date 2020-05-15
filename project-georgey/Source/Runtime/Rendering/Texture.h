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

	void SetData(ImageData* data);
	void SetData(void* data, int width, int height, EImageEncoding encoding, bool invertedPixels = false);

	void Bind(unsigned int slot = 0);
	void UnBind();

	unsigned int GetWidth();
	unsigned int GetHeight();
	EImageEncoding GetImageEncoding();

	bool operator==(const Texture& other) const;
	bool operator!=(const Texture& other) const;
};