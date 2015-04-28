#ifndef _LRENDER_SHADER_H_
#define _LRENDER_SHADER_H_

typedef struct LRenderShader LRenderShader;

#include "lrender.h"

struct LRenderShader {
	GLuint program;

	GLuint vertex;
	GLuint fragment;
};

bool 			LRenderShader_use_as_default 	(GLenum, const char*);

LRenderShader* 	LRenderShader_create 			(void);
void 			LRenderShader_free 				(LRenderShader*);

bool 			LRenderShader_load_default 		(LRenderShader*, GLenum);
bool 			LRenderShader_load 				(LRenderShader*, GLenum, const char*);

#endif
