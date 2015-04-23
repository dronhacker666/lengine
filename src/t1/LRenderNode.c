#include "lrender.h"

LRenderNode* LRenderNode_create(LRenderNodeType type)
{
	LRenderNode* node = calloc(1, sizeof(LRenderNode));
	node->type = type;

	switch(node->type){
		case LRENDER_NODE_SPRITE: node->sprite = LRenderNodeSprite_create(); break;
		default: break;
	}

	return node;
}

void LRenderNode_free(LRenderNode* node)
{
	switch(node->type){
		case LRENDER_NODE_SPRITE: LRenderNodeSprite_free(node->sprite); break;
		default: break;
	}
	free(node);
}

void LRenderNode_draw(LRenderNode* node)
{

/*	glMatrixMode(GL_MODELVIEW);

	Mat4x4 model_view;
	gen_translation_mat4x4(&model_view, 0.0f, 0.5f, 0.0f);

	glLoadMatrixf((float*)&model_view);*/


	// gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

	switch(node->type){
		case LRENDER_NODE_SPRITE: LRenderNodeSprite_draw(node->sprite); break;
		default: break;
	}
}

void LRenderNode_set_position(LRenderNode* node, float x, float y, float z)
{
	node->position[0] = x;
	node->position[1] = y;
	node->position[2] = z;
}
