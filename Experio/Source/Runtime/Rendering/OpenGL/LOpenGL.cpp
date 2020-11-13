#include "LOpenGL.h"
#include "GL/wglext.h"

size_t LOpenGL::GetSizeOfType(unsigned int type)
{
	switch (type)
	{
	case GL_BYTE:
	case GL_UNSIGNED_BYTE:
		return 1;
	case GL_SHORT:
	case GL_UNSIGNED_SHORT:
	case GL_HALF_FLOAT:
		return 2;
	case GL_FLOAT:
	case GL_INT:
	case GL_UNSIGNED_INT:
	case GL_FIXED:
		return 4;
	case GL_DOUBLE:
		return 8;
	}
	return 0;
}

size_t LOpenGL::GetSizeOfType(EDataType type)
{
	return GetSizeOfType((unsigned int)type);
}

size_t LOpenGL::GetImageFormat(EImageEncoding encoding, EImageFileType fileType)
{
	switch (fileType)
	{
	case EImageFileType::BMP:
		if (encoding == EImageEncoding::Truecolor)
		{
			return GL_BGR;
		}
		if (encoding == EImageEncoding::TruecolorAlpha)
		{
			return GL_BGRA;
		}
		return GL_RGB;
	}

	return GL_RGB;
}

size_t LOpenGL::GetInternalFormat(EImageEncoding encoding, EImageFileType fileType)
{
	switch (fileType)
	{
	case EImageFileType::BMP:
		if (encoding == EImageEncoding::Truecolor)
		{
			return GL_RGB8;
		}
		if (encoding == EImageEncoding::TruecolorAlpha)
		{
			return GL_RGBA8;
		}
	}
	return 0;;
}

EDataType LOpenGL::StringToDataType(std::string string)
{
	if (string == "FLOAT") return EDataType::FLOAT;

	if (string == "INT") return EDataType::INT;

	if (string == "UINT") return EDataType::UNSIGNED_INT;

	// Add stuff here
	return EDataType::NONE;
}

bool LOpenGL::WGLExtensionSupported(const char * extensionName)
{
	// this is pointer to function which returns pointer to string with list of all wgl extensions
	PFNWGLGETEXTENSIONSSTRINGEXTPROC _wglGetExtensionsStringEXT = NULL;

	// determine pointer to wglGetExtensionsStringEXT function
	_wglGetExtensionsStringEXT = (PFNWGLGETEXTENSIONSSTRINGEXTPROC)wglGetProcAddress("wglGetExtensionsStringEXT");

	if (strstr(_wglGetExtensionsStringEXT(), extensionName) == NULL)
	{
		return false;
	}

	return true;
}

uint16_t LOpenGL::GLSLVersionToPreprocessor(uint8_t major, uint8_t minor)
{
	return major * 100 + minor * 10;
}

std::string LOpenGL::GLSLVersionToPreprocessorStr(uint8_t major, uint8_t minor)
{
	return "#version " + std::to_string(GLSLVersionToPreprocessor(major, minor));
}
