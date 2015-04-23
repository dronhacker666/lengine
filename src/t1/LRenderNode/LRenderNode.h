#ifndef _LRENDER_NODE_H_
#define _LRENDER_NODE_H_

typedef struct LRenderNode LRenderNode;

typedef enum {
	LRENDER_NODE_TYPELESS,
	LRENDER_NODE_TESTBOX,
	LRENDER_NODE_SPRITE,
	LRENDER_NODE_DIRECT_LIGHT,
} LRenderNodeType;

#include "../lrender.h"
#include "LRenderNodeSprite.h"
#include "LRenderNodeTestBox.h"
#include "LRenderNodeDirectLight.h"

/**
 * LRenderNode
 */

struct LRenderNode {
	LRenderNodeType type;
	bool visible;
	bool need_predraw;
	bool need_draw;

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
void 			LRenderNode_predraw 		(LRenderNode*, LRenderScene*);

void 			LRenderNode_set_position 	(LRenderNode*, float, float, float);

#endif
