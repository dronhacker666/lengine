#ifndef _L_RENDER_H_
#define _L_RENDER_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "OpenGL.h"

#include "lmath.h"
#include "../lib/lib.h"

extern GLuint shader_program;

typedef struct LRender LRender;
typedef struct LRenderScene LRenderScene;
typedef struct LRenderCamera LRenderCamera;

typedef struct LRenderNode LRenderNode;
typedef struct LRenderNodeSprite LRenderNodeSprite;

/**
 * LRender
 */

struct LRender {

};

LRender* 		LRender_create 			(void);
void 			LRender_free 			(LRender*);

void 			LRender_draw 			(LRender*, LRenderScene*, LRenderCamera*);

/**
 * LRenderScene
 */

struct LRenderScene {
	Array* geometry;
	Array* lights;
};

LRenderScene*	LRenderScene_create 		(void);
void 			LRenderScene_free 			(LRenderScene*);

void 			LRenderScene_append_node 	(LRenderScene*, LRenderNode*);
void 			LRenderScene_wait_load 		(LRenderScene*);


/**
 * LRenderCamera
 */

struct LRenderCamera {
	Mat4x4 projection;
	Vec3 position;
};
LRenderCamera*	LRenderCamera_create 	(void);
void 			LRenderCamera_free 		(LRenderCamera*);



/**
 * LRenderNode
 */

typedef enum {
	LRENDER_NODE_TYPELESS,
	LRENDER_NODE_SPRITE,
	LRENDER_NODE_LIGHT,
} LRenderNodeType;

struct LRenderNode {
	LRenderNodeType type;
	Vec3 position;
	Vec3 direction;
	bool ready;
	union {
		LRenderNodeSprite* sprite;
	};
};

LRenderNode* 	LRenderNode_create 			(LRenderNodeType);
void		 	LRenderNode_free 			(LRenderNode*);

void 			LRenderNode_draw 			(LRenderNode*);
void 			LRenderNode_set_position 	(LRenderNode*, float, float, float);

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
