#include "lrender.h"

LRenderScene* LRenderScene_create(void)
{
	LRenderScene* scene = calloc(1, sizeof(LRenderScene));
	scene->geometry = array_create();
	scene->lights = array_create();
	return scene;
}

void LRenderScene_free(LRenderScene* scene)
{
	array_free(scene->geometry);
	array_free(scene->lights);
	free(scene);
}

void LRenderScene_append_node(LRenderScene* scene, LRenderNode* node)
{
	switch(node->type){
		case LRENDER_NODE_SPRITE:
			array_push(scene->geometry, &node);
		break;
		case LRENDER_NODE_LIGHT:
			array_push(scene->lights, &node);
		break;
		default: break;
	}
}

void LRenderScene_wait_load(LRenderScene* scene)
{

}
