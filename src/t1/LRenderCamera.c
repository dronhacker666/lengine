#include "lrender.h"

LRenderCamera* LRenderCamera_create(void)
{
	LRenderCamera* camera = calloc(1, sizeof(LRenderCamera));

	return camera;
}

void LRenderCamera_free(LRenderCamera* camera)
{
	free(camera);
}
