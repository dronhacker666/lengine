#ifndef _LRENDER_SHADER_H_
#define _LRENDER_SHADER_H_

#include "lrender.h"

typedef struct LRenderShader LRenderShader;

struct LRenderShader {
	GLuint program;
};

LRenderShader* 	LRenderShader_create 		(void);
void 			LRenderShader_free 			(LRenderShader*);

bool 			LRenderShader_from_file 		(LRenderShader*, const char*);
LRenderShader* 	LRenderShader_create_from_file 	(const char*);

#endif
