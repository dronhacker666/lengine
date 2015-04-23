#ifndef _LRENDER_NODE_H_
#define _LRENDER_NODE_H_

typedef struct LRenderNode LRenderNode;

#include "../lrender.h"
#include "LRenderNodeSprite.h"
#include "LRenderNodeTestBox.h"
#include "LRenderNodeDirectLight.h"

typedef enum {
	LRENDER_NODE_GEOMETRY,
	LRENDER_NODE_LIGHT,
} LRenderNodeClass;

typedef enum {
	LRENDER_NODE_TYPELESS,
	LRENDER_NODE_TESTBOX,
	LRENDER_NODE_SPRITE,
	LRENDER_NODE_DIRECT_LIGHT,
} LRenderNodeType;

/**
 * LRenderNode
 */

struct LRenderNode {
	LRenderNodeClass class;
	LRenderNodeType type;
	bool visible;
	Vec3 position;
	Vec3 direction;
	union {
		LRenderNodeDirectLight* direct_light;
		LRenderNodeTestBox* testbox;
		LRenderNodeSprite* sprite;
	};
};

LRenderNode* 	LRenderNode_create 			(LRenderNodeType);
void		 	LRenderNode_free 			(LRenderNode*);
void 			LRenderNode_draw 			(LRenderNode*);

void 			LRenderNode_set_position 	(LRenderNode*, float, float, float);

#endif
