#ifndef _L_RENDER_H_
#define _L_RENDER_H_

typedef struct LRender LRender;
typedef struct LRenderScene LRenderScene;
typedef struct LRenderTarget LRenderTarget;
typedef struct LRenderCamera LRenderCamera;

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "OpenGL.h"

#include "lmath.h"
#include "../lib/lib.h"

#include "LRenderNode/LRenderNode.h"

extern GLuint shader_program;

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
 * LRenderTarget
 */

typedef enum {
	LRENDER_TARGET_SCREEN,
	LRENDER_TARGET_TEXTURE,
	LRENDER_TARGET_GBUFFER,
} LRenderTargetType;

struct LRenderTarget {
	LRenderTargetType type;
	unsigned width;
	unsigned height;
	float fov;
	float znear;
	float zfar;
};

LRenderTarget*	LRenderTarget_create 	(void);
void 			LRenderTarget_free 		(LRenderTarget*);


/**
 * LRenderCamera
 */

struct LRenderCamera {
	Mat4x4 projection;
	Vec3 position;
	Vec3 direction;

	LRenderTarget* target;
};
LRenderCamera*	LRenderCamera_create 	(void);
void 			LRenderCamera_free 		(LRenderCamera*);

void 			LRenderCamera_set_projection_matrix 	(LRenderCamera*, Mat4x4);
void 			LRenderCamera_set_perspective_matrix 	(LRenderCamera*);
void 			LRenderCamera_set_ortho_matrix 			(LRenderCamera*);

#endif
