#include "LRenderNode.h"

LRenderNode* LRenderNode_create(LRenderNodeType type)
{
	LRenderNode* node = calloc(1, sizeof(LRenderNode));
	node->visible = true;
	node->type = type;

	switch(node->type){
		case LRENDER_NODE_DIRECT_LIGHT: node->direct_light = LRenderNodeDirectLight_create(node); break;
		case LRENDER_NODE_TESTBOX: 		node->testbox = LRenderNodeTestBox_create(node); break;
		case LRENDER_NODE_SPRITE: 		node->sprite = LRenderNodeSprite_create(node); break;
		default: break;
	}

	return node;
}

void LRenderNode_free(LRenderNode* node)
{
	switch(node->type){
		case LRENDER_NODE_DIRECT_LIGHT: 	LRenderNodeDirectLight_free(node->direct_light); 	break;
		case LRENDER_NODE_TESTBOX: 			LRenderNodeTestBox_free(node->testbox); 			break;
		case LRENDER_NODE_SPRITE: 			LRenderNodeSprite_free(node->sprite); 				break;
		default: break;
	}
	free(node);
}

void LRenderNode_predraw(LRenderNode* node, LRenderScene* scene)
{
	switch(node->type){
		case LRENDER_NODE_DIRECT_LIGHT: LRenderNodeDirectLight_predraw(node->direct_light, scene); break;
		default: break;
	}
}

void LRenderNode_draw(LRenderNode* node)
{
	Mat4x4 model_view;
	gen_translation_mat4x4(model_view, node->position[0], node->position[1], node->position[2]);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "modelMatrix"), 1, GL_TRUE, (const GLfloat*)model_view);

	switch(node->type){
		case LRENDER_NODE_TESTBOX: 	LRenderNodeTestBox_draw(node->testbox); break;
		case LRENDER_NODE_SPRITE: 	LRenderNodeSprite_draw(node->sprite); 	break;
		default: break;
	}
}

void LRenderNode_set_position(LRenderNode* node, float x, float y, float z)
{
	node->position[0] = x;
	node->position[1] = y;
	node->position[2] = z;
}
