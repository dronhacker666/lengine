#ifndef LRENDER_NODE_DIRECTLIGHT_H_
#define LRENDER_NODE_DIRECTLIGHT_H_

typedef struct LRenderNodeDirectLight LRenderNodeDirectLight;

#include "LRenderNode.h"

/**
 * LRenderNodeDirectLight
 */
struct LRenderNodeDirectLight {
	float range;
	Vec3 color;
	bool cast_shadow;

	LRenderCamera* _camera;
};

LRenderNodeDirectLight* 	LRenderNodeDirectLight_create 	(void);
void 						LRenderNodeDirectLight_free 	(LRenderNodeDirectLight*);
void 						LRenderNodeDirectLight_draw 	(LRenderNodeDirectLight*);


#endif
