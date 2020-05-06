#include "LOpenGL.h"

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
