#pragma once
#include "GL/glew.h"
#include "../../Files/Images/ImageReader.h"
#include "../VertexBuffer.h"
#include <string>

class LOpenGL
{
public:
	static std::string ErrorToString(GLenum errorCode);

	static size_t GetSizeOfType(unsigned int type);
	static size_t GetSizeOfType(EDataType type);

	static size_t GetImageFormat(EImageInternalFormat format);

	static size_t GetInternalFormat(EImageEncoding encoding);

	static EDataType StringToDataType(const std::string& string);

	static bool WGLExtensionSupported(const char* extensionName);

	static uint16_t GLSLVersionToPreprocessor(uint8_t major, uint8_t minor);
	static std::string GLSLVersionToPreprocessorStr(uint8_t major, uint8_t minor);
};