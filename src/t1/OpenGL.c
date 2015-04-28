#include "OpenGL.h"

#ifdef _WIN32
	#define glGetProcAddress(NAME) wglGetProcAddress(NAME)
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
#elif __linux
	#define glGetProcAddress(NAME) glXGetProcAddress((const GLubyte*)NAME)
	PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = NULL;
#endif

#include "OpenGLExt.inc"

GLint initOpenGLExt(void)
{
	#include "OpenGLExtInit.inc"
	return GL_TRUE;
}
