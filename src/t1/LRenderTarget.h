#ifndef _LRENDER_TARGET_H_
#define _LRENDER_TARGET_H_

typedef struct LRenderTarget LRenderTarget;

#include "lrender.h"

/**
 * LRenderTarget
 */

struct LRenderTarget {
	unsigned width;
	unsigned height;

	GLuint FBO;
	GLuint color0;
	GLuint color1;
	GLuint depth;
};

LRenderTarget*	LRenderTarget_create 	(unsigned, unsigned);
void 			LRenderTarget_free 		(LRenderTarget*);

#endif
