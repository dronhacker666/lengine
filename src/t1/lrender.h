#ifndef _L_RENDER_H_
#define _L_RENDER_H_

typedef struct LRender LRender;
typedef struct LRenderScene LRenderScene;
typedef struct LRenderCamera LRenderCamera;

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdint.h>
#include <unistd.h>

#include "OpenGL.h"

#include "lmath.h"
#include "../lib/lib.h"

#include "LRenderShader.h"
#include "LRenderTarget.h"
#include "LRenderNode/LRenderNode.h"

extern GLuint shader_program;

/**
 * LRender
 */

struct LRender {
	LRenderCamera* camera;
	LRenderTarget* target;

#ifdef _WIN32

#elif __linux
	Display* display;
	Window root;
	Window window;
	GLXContext opengl_context;
	XVisualInfo* vi;
#endif
};

LRender* 		LRender_create 			(void);
void 			LRender_free 			(LRender*);

void 			LRender_draw 			(LRender*, LRenderScene*);

/**
 * LRenderScene
 */

struct LRenderScene {
	Array* predraw_node_list;
	Array* draw_node_list;
};

LRenderScene*	LRenderScene_create 		(void);
void 			LRenderScene_free 			(LRenderScene*);

void 			LRenderScene_append_node 	(LRenderScene*, LRenderNode*);
void 			LRenderScene_wait_load 		(LRenderScene*);



/**
 * LRenderCamera
 */

struct LRenderCamera {
	Vec3 position;
	Vec3 rotation;
	float fov;
	float znear;
	float zfar;
};
LRenderCamera*	LRenderCamera_create 	(void);
void 			LRenderCamera_free 		(LRenderCamera*);

void 			LRenderCamera_rasterization_scene 		(LRenderCamera*, LRenderScene*, LRenderTarget*);

#endif
