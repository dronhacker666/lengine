#include "LRenderNodeDirectLight.h"

LRenderNodeDirectLight* LRenderNodeDirectLight_create(LRenderNode* node)
{
	node->need_predraw = true;

	LRenderNodeDirectLight* light = calloc(1, sizeof(LRenderNodeDirectLight));

	light->_camera = LRenderCamera_create();

	return light;
}

void LRenderNodeDirectLight_free(LRenderNodeDirectLight* light)
{
	LRenderCamera_free(light->_camera);
	free(light);
}

void LRenderNodeDirectLight_predraw(LRenderNodeDirectLight* light, LRender* render, LRenderScene* scene)
{
	if(light->cast_shadow){
		//LRenderCamera_rasterization_scene(light->_camera, scene, NULL);
	}
}

