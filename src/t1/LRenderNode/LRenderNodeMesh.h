#ifndef _LRENDER_NODE_MESH_H_
#define _LRENDER_NODE_MESH_H_

typedef struct LRenderNodeMesh LRenderNodeMesh;

#include "LRenderNode.h"

/**
 * LRenderNodeMesh
 */

struct LRenderNodeMesh {
	GLuint VAO;
	GLuint VBO;
	size_t vertex_count;
};

LRenderNodeMesh* 	LRenderNodeMesh_create 	(LRenderNode*);
void 				LRenderNodeMesh_free 	(LRenderNodeMesh*);
void 				LRenderNodeMesh_draw 	(LRenderNodeMesh*);

void 				LRenderNodeMesh_load 	(LRenderNodeMesh*, const char*);

#endif
