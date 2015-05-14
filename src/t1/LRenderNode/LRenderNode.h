#ifndef _LRENDER_NODE_H_
#define _LRENDER_NODE_H_

typedef struct LRenderNode LRenderNode;

typedef enum {
	LRENDER_NODE_TYPELESS,
	LRENDER_NODE_TESTBOX,
	LRENDER_NODE_SPRITE,
	LRENDER_NODE_DIRECT_LIGHT,
	LRENDER_NODE_MESH,
} LRenderNodeType;

#include "../lrender.h"
#include "LRenderNodeSprite.h"
#include "LRenderNodeTestBox.h"
#include "LRenderNodeDirectLight.h"
#include "LRenderNodeMesh.h"

/**
 * LRenderNode
 */

struct LRenderNode {
	LRenderNodeType type;
	bool visible;
	bool need_predraw;
	bool need_draw;

	LRenderShader* shader;

	Vec3 position;
	Vec3 rotation;
	union {
		LRenderNodeDirectLight* direct_light;
		LRenderNodeTestBox* testbox;
		LRenderNodeSprite* sprite;
		LRenderNodeMesh* mesh;
	};
};

LRenderNode* 	LRenderNode_create 			(LRenderNodeType);
void		 	LRenderNode_free 			(LRenderNode*);
void 			LRenderNode_draw 			(LRenderNode*);
void 			LRenderNode_predraw 		(LRenderNode*, LRender*, LRenderScene*);

void 			LRenderNode_set_position 	(LRenderNode*, float, float, float);
void 			LRenderNode_set_rotation 	(LRenderNode*, float, float, float);

#endif
