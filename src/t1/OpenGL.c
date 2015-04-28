#include "OpenGL.h"

#ifdef _WIN32
	#define glGetProcAddress(NAME) wglGetProcAddress(NAME)
	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
#elif __linux
	#define glGetProcAddress(NAME) glXGetProcAddress((const GLubyte*)NAME)
	PFNGLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = NULL;
#endif




// PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
PFNGLGENERATEMIPMAPPROC glGenerateMipmap = NULL;

//FBO
PFNGLGENFRAMEBUFFERSPROC 			glGenFramebuffers 	 		= NULL;
PFNGLDELETEFRAMEBUFFERSPROC     	glDeleteFramebuffers 		= NULL;
PFNGLGENRENDERBUFFERSPROC 			glGenRenderbuffers 			= NULL;
PFNGLBINDFRAMEBUFFERPROC 			glBindFramebuffer 			= NULL;
PFNGLBINDRENDERBUFFERPROC 			glBindRenderbuffer 			= NULL;
PFNGLRENDERBUFFERSTORAGEPROC 		glRenderbufferStorage 		= NULL;
PFNGLFRAMEBUFFERRENDERBUFFERPROC 	glFramebufferRenderbuffer 	= NULL;
PFNGLFRAMEBUFFERTEXTURE2DPROC 		glFramebufferTexture2D 		= NULL;
PFNGLDRAWBUFFERSPROC 				glDrawBuffers 				= NULL;
PFNGLBINDFRAGDATALOCATIONPROC 		glBindFragDataLocation 		= NULL;
// VAO
PFNGLGENVERTEXARRAYSPROC    glGenVertexArrays    = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC    glBindVertexArray    = NULL;
// VBO
PFNGLGENBUFFERSPROC    glGenBuffers    = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC    glBindBuffer    = NULL;
PFNGLBUFFERDATAPROC    glBufferData    = NULL;
PFNGLBUFFERSUBDATAPROC glBufferSubData = NULL;
// Shaders
PFNGLCREATEPROGRAMPROC     glCreateProgram     = NULL;
PFNGLDELETEPROGRAMPROC     glDeleteProgram     = NULL;
PFNGLLINKPROGRAMPROC       glLinkProgram       = NULL;
PFNGLVALIDATEPROGRAMPROC   glValidateProgram   = NULL;
PFNGLUSEPROGRAMPROC        glUseProgram        = NULL;
PFNGLGETPROGRAMIVPROC      glGetProgramiv      = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLCREATESHADERPROC      glCreateShader      = NULL;
PFNGLDELETESHADERPROC      glDeleteShader      = NULL;
PFNGLSHADERSOURCEPROC      glShaderSource      = NULL;
PFNGLCOMPILESHADERPROC     glCompileShader     = NULL;
PFNGLATTACHSHADERPROC      glAttachShader      = NULL;
PFNGLDETACHSHADERPROC      glDetachShader      = NULL;
PFNGLGETSHADERIVPROC       glGetShaderiv       = NULL;
PFNGLGETSHADERINFOLOGPROC  glGetShaderInfoLog  = NULL;
// Shaders attributes
PFNGLGETATTRIBLOCATIONPROC        glGetAttribLocation        = NULL;
PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
// Shaders uniforms
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORMMATRIX4FVPROC   glUniformMatrix4fv   = NULL;
PFNGLUNIFORM1FPROC   		glUniform1f		     = NULL;
PFNGLUNIFORM2FPROC   		glUniform2f		     = NULL;
PFNGLUNIFORM4FPROC   		glUniform4f		     = NULL;
PFNGLUNIFORM1IPROC   		glUniform1i		     = NULL;
PFNGLUNIFORM2IPROC   		glUniform2i		     = NULL;
PFNGLUNIFORM2FVPROC			glUniform2fv		 = NULL;
PFNGLUNIFORM3FVPROC			glUniform3fv		 = NULL;
PFNGLUNIFORM2IVPROC			glUniform2iv		 = NULL;

GLint initOpenGLExt(void)
{
	// glActiveTexture = (PFNGLACTIVETEXTUREPROC)glGetProcAddress("glActiveTexture");
	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glGetProcAddress("glGenerateMipmap");
	
	//FBO
	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)glGetProcAddress("glGenFramebuffers");
	glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)glGetProcAddress("glDeleteFramebuffers");
	glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)glGetProcAddress("glGenRenderbuffers");
	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)glGetProcAddress("glBindFramebuffer");
	glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)glGetProcAddress("glBindRenderbuffer");
	glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)glGetProcAddress("glRenderbufferStorage");
	glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)glGetProcAddress("glFramebufferRenderbuffer");
	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)glGetProcAddress("glFramebufferTexture2D");
	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)glGetProcAddress("glDrawBuffers");
	glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)glGetProcAddress("glBindFragDataLocation");
	//VAO
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glGetProcAddress("glGenVertexArrays");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glGetProcAddress("glDeleteVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glGetProcAddress("glBindVertexArray");
	// VBO
	glGenBuffers = (PFNGLGENBUFFERSPROC)glGetProcAddress("glGenBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glGetProcAddress("glDeleteBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)glGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)glGetProcAddress("glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)glGetProcAddress("glBufferSubData");
	// Shaders
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)glGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glGetProcAddress("glDeleteProgram");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)glGetProcAddress("glLinkProgram");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)glGetProcAddress("glValidateProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)glGetProcAddress("glUseProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glGetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glGetProcAddress("glGetProgramInfoLog");
	glCreateShader = (PFNGLCREATESHADERPROC)glGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)glGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)glGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)glGetProcAddress("glCompileShader");
	glAttachShader = (PFNGLATTACHSHADERPROC)glGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)glGetProcAddress("glDetachShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)glGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glGetProcAddress("glGetShaderInfoLog");
	// Shaders attributes
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glGetProcAddress("glGetAttribLocation");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glGetProcAddress("glVertexAttribPointer");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glGetProcAddress("glDisableVertexAttribArray");
	// Shaders uniforms
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glGetProcAddress("glGetUniformLocation");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glGetProcAddress("glUniformMatrix4fv");
	glUniform1f = (PFNGLUNIFORM1FPROC)glGetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)glGetProcAddress("glUniform2f");
	glUniform4f = (PFNGLUNIFORM4FPROC)glGetProcAddress("glUniform4f");
	glUniform1i = (PFNGLUNIFORM1IPROC)glGetProcAddress("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC)glGetProcAddress("glUniform2i");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM2FVPROC)glGetProcAddress("glUniform3fv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)glGetProcAddress("glUniform2iv");

	return GL_TRUE;
}
