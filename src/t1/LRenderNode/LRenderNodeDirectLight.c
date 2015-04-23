#include "LRenderNodeDirectLight.h"

LRenderNodeDirectLight* LRenderNodeDirectLight_create(void)
{
	LRenderNodeDirectLight* light = calloc(1, sizeof(LRenderNodeDirectLight));

	light->_camera = LRenderCamera_create();

	return light;
}

void LRenderNodeDirectLight_free(LRenderNodeDirectLight* light)
{
	LRenderCamera_free(light->_camera);
	free(light);
}

void LRenderNodeDirectLight_draw(LRenderNodeDirectLight* light)
{
	if(light->cast_shadow){

	}
}

