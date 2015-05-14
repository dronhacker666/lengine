include func.mk

.PHONY: genOpenGLExt

# FBO
OPENGL_EXT += glGenFramebuffers
OPENGL_EXT += glDeleteFramebuffers
OPENGL_EXT += glGenRenderbuffers
OPENGL_EXT += glBindFramebuffer
OPENGL_EXT += glBindRenderbuffer
OPENGL_EXT += glRenderbufferStorage
OPENGL_EXT += glFramebufferRenderbuffer
OPENGL_EXT += glFramebufferTexture2D
OPENGL_EXT += glDrawBuffers
OPENGL_EXT += glBindFragDataLocation
OPENGL_EXT += glCheckFramebufferStatus

# VAO
OPENGL_EXT += glGenVertexArrays
OPENGL_EXT += glDeleteVertexArrays
OPENGL_EXT += glBindVertexArray

# VBO
OPENGL_EXT += glGenBuffers
OPENGL_EXT += glDeleteBuffers
OPENGL_EXT += glBindBuffer
OPENGL_EXT += glBufferData
OPENGL_EXT += glBufferSubData

# Shaders
OPENGL_EXT += glCreateProgram
OPENGL_EXT += glDeleteProgram
OPENGL_EXT += glLinkProgram
OPENGL_EXT += glValidateProgram
OPENGL_EXT += glUseProgram
OPENGL_EXT += glGetProgramiv
OPENGL_EXT += glGetProgramInfoLog
OPENGL_EXT += glCreateShader
OPENGL_EXT += glDeleteShader
OPENGL_EXT += glShaderSource
OPENGL_EXT += glCompileShader
OPENGL_EXT += glAttachShader
OPENGL_EXT += glDetachShader
OPENGL_EXT += glGetShaderiv
OPENGL_EXT += glGetShaderInfoLog

# Shaders attributes
OPENGL_EXT += glGetAttribLocation
OPENGL_EXT += glVertexAttribPointer
OPENGL_EXT += glEnableVertexAttribArray
OPENGL_EXT += glDisableVertexAttribArray

# Shaders uniforms
OPENGL_EXT += glGetUniformLocation
OPENGL_EXT += glUniformMatrix4fv
OPENGL_EXT += glUniform1f
OPENGL_EXT += glUniform2f
OPENGL_EXT += glUniform4f
OPENGL_EXT += glUniform1i
OPENGL_EXT += glUniform2i
OPENGL_EXT += glUniform2fv
OPENGL_EXT += glUniform3fv
OPENGL_EXT += glUniform2iv

genOpenGLExt: $(lastword $(MAKEFILE_LIST))
	@echo $(foreach ext, $(OPENGL_EXT), "extern PFN"$(call uppercase,$(ext))"PROC "$(ext)";\n") > OpenGLExtDef.inc
	@echo $(foreach ext, $(OPENGL_EXT), "PFN"$(call uppercase,$(ext))"PROC "$(ext)" = NULL;\n") > OpenGLExt.inc
	@echo $(foreach ext, $(OPENGL_EXT),  $(ext)" = (PFN"$(call uppercase,$(ext))"PROC)glGetProcAddress(\""$(ext)"\");\n") > OpenGLExtInit.inc
