#include "LRenderNode.h"

LRenderNode* LRenderNode_create(LRenderNodeType type)
{
	LRenderNode* node = calloc(1, sizeof(LRenderNode));
	node->visible = true;
	node->type = type;

	switch(node->type){
		case LRENDER_NODE_DIRECT_LIGHT: node->direct_light = LRenderNodeDirectLight_create(node); 	break;
		case LRENDER_NODE_TESTBOX: 		node->testbox = LRenderNodeTestBox_create(node); 			break;
		case LRENDER_NODE_SPRITE: 		node->sprite = LRenderNodeSprite_create(node); 				break;
		case LRENDER_NODE_MESH: 		node->mesh = LRenderNodeMesh_create(node); 					break;
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
		case LRENDER_NODE_MESH: 			LRenderNodeMesh_free(node->mesh); 					break;
		default: break;
	}
	free(node);
}

void LRenderNode_predraw(LRenderNode* node, LRender* render, LRenderScene* scene)
{
	switch(node->type){
		case LRENDER_NODE_DIRECT_LIGHT: LRenderNodeDirectLight_predraw(node->direct_light, render, scene); break;
		default: break;
	}
}

void LRenderNode_draw(LRenderNode* node)
{
	Mat4x4 model_view;
	Mat4x4 rotation_mat;
	gen_translation_mat4x4(model_view, node->position[0], node->position[1], node->position[2]);
	gen_rotation_mat4x4(rotation_mat, node->rotation[0], node->rotation[1], node->rotation[2]);

	multiple_mat4x4(model_view, model_view, rotation_mat);

	//glUseProgram(node->shader->program);

	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_TRUE, (const GLfloat*)model_view);

	switch(node->type){
		case LRENDER_NODE_TESTBOX: 	LRenderNodeTestBox_draw(node->testbox); break;
		case LRENDER_NODE_SPRITE: 	LRenderNodeSprite_draw(node->sprite); 	break;
		case LRENDER_NODE_MESH: 	LRenderNodeMesh_draw(node->mesh); 		break;
		default: break;
	}
}

void LRenderNode_set_position(LRenderNode* node, float x, float y, float z)
{
	node->position[0] = x;
	node->position[1] = y;
	node->position[2] = z;
}

void LRenderNode_set_rotation(LRenderNode* node, float x, float y, float z)
{
	node->rotation[0] = x;
	node->rotation[1] = y;
	node->rotation[2] = z;
}
