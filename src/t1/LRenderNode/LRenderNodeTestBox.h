#ifndef _LRENDER_NODE_TESTBOX_H_
#define _LRENDER_NODE_TESTBOX_H_

typedef struct LRenderNodeTestBox LRenderNodeTestBox;

#include "LRenderNode.h"

/**
 * LRenderNodeTestBox
 */

struct LRenderNodeTestBox {
	Vec3 color;
	unsigned width;
	unsigned height;

	GLuint VAO;
	GLuint VBO[2];
};

LRenderNodeTestBox* 	LRenderNodeTestBox_create 	(void);
void 					LRenderNodeTestBox_free 	(LRenderNodeTestBox*);
void 					LRenderNodeTestBox_draw 	(LRenderNodeTestBox*);

#endif
