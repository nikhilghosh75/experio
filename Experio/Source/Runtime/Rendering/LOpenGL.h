#pragma once
#include "GL/glew.h"
#include "../Files/Images/ImageReader.h"
#include "VertexBuffer.h"

class LOpenGL
{
public:
	static size_t GetSizeOfType(unsigned int type);
	static size_t GetSizeOfType(EDataType type);

	static size_t GetImageFormat(EImageEncoding encoding, EImageFileType fileType);

	static size_t GetInternalFormat(EImageEncoding encoding, EImageFileType fileType);

	static EDataType StringToDataType(std::string string);

	static bool WGLExtensionSupported(const char* extensionName);
};