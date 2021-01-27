#include "LOpenGL.h"
#include "GL/wglext.h"

std::string LOpenGL::ErrorToString(GLenum errorCode)
{
	switch (errorCode)
	{
	case GL_NO_ERROR: return "";
	case GL_INVALID_ENUM: return "INVALID ENUM";
	case GL_INVALID_VALUE: return "INVALID_VALUE";
	case GL_INVALID_OPERATION: return "INVALID OPERATION";
	case GL_STACK_OVERFLOW: return "STACK OVERFLOW";
	case GL_STACK_UNDERFLOW: return "STACK UNDERFLOW";
	case GL_OUT_OF_MEMORY: return "OUT OF MEMORY";
	case GL_INVALID_FRAMEBUFFER_OPERATION: return "INVALID FRAMEBUFFER OPERATION";
	}
	return "";
}

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

size_t LOpenGL::GetImageFormat(EImageInternalFormat format)
{
	switch (format)
	{
	case EImageInternalFormat::R: return GL_RED;
	case EImageInternalFormat::RG: return GL_RG;
	case EImageInternalFormat::RGB: return GL_RGB;
	case EImageInternalFormat::RGBA: return GL_RGBA;
	case EImageInternalFormat::BGR: return GL_BGR;
	case EImageInternalFormat::BGRA: return GL_BGRA;
	}

	return GL_RGB;
}

size_t LOpenGL::GetInternalFormat(EImageEncoding encoding)
{
	switch (encoding)
	{
	case EImageEncoding::Grayscale: return GL_RED;
	case EImageEncoding::GrayscaleAlpha: return GL_RG8;
	case EImageEncoding::Truecolor: return GL_RGB8;
	case EImageEncoding::TruecolorAlpha: return GL_RGBA8;
	}
	return GL_RGBA;
}

EDataType LOpenGL::StringToDataType(const std::string& string)
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
