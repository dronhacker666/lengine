#include "lrender.h"

LRenderScene* LRenderScene_create(void)
{
	LRenderScene* scene = calloc(1, sizeof(LRenderScene));
	scene->predraw_node_list = array_create();
	scene->draw_node_list = array_create();
	return scene;
}

void LRenderScene_free(LRenderScene* scene)
{
	array_free(scene->predraw_node_list);
	array_free(scene->draw_node_list);
	free(scene);
}

void LRenderScene_append_node(LRenderScene* scene, LRenderNode* node)
{
	if(node->need_predraw){
		array_push(scene->predraw_node_list, &node);
	}
	if(node->need_draw){
		array_push(scene->draw_node_list, &node);
	}
}

void LRenderScene_wait_load(LRenderScene* scene)
{

}
