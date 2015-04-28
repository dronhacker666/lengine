#ifndef _OPEN_GL_H_
#define _OPEN_GL_H_

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

GLint initOpenGLExt(void);

/* OPENGL EXTENSIONS */

#ifdef _WIN32
	extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribs;
#elif __linux
	extern PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB;
#endif

#include "OpenGLExtDef.inc"

#endif
