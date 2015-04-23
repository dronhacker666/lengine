#ifndef _LRENDER_NODE_SPRITE_H_
#define _LRENDER_NODE_SPRITE_H_

typedef struct LRenderNodeSprite LRenderNodeSprite;

#include "LRenderNode.h"

/**
 * LRenderNodeSprite
 */
struct LRenderNodeSprite {
	wchar_t* file_name;
	Vec3 color;
	unsigned width;
	unsigned height;

	GLuint VAO;
	GLuint VBO;
};

LRenderNodeSprite* 	LRenderNodeSprite_create 	(void);
void 				LRenderNodeSprite_free 		(LRenderNodeSprite*);
void 				LRenderNodeSprite_draw 		(LRenderNodeSprite*);

void 				LRenderNodeSprite_set_color (LRenderNodeSprite*, float, float, float);
bool 				LRenderNodeSprite_set_image (LRenderNodeSprite*, const wchar_t*);

#endif
