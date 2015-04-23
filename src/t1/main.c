#include "lrender.h"

int main(void)
{
	LRender* render = LRender_create();
	LRenderCamera* camera = LRenderCamera_create();
		gen_identity_mat4x4(camera->projection);

	LRenderScene* scene = LRenderScene_create();

	LRenderNode* node = LRenderNode_create(LRENDER_NODE_SPRITE);
	LRenderNode_set_position(node, 0.0f, 0.0f, 0.0f);
	LRenderNodeSprite_set_color(node->sprite, 1.0f, 0.2f, 0.3f);
	LRenderScene_append_node(scene, node);


	LRenderScene_wait_load(scene);

	sleep(1);
	LRender_draw(render, scene, camera);
	sleep(1);
	LRender_draw(render, scene, camera);
	sleep(1);

	LRenderCamera_free(camera);
	LRenderScene_free(scene);
	LRender_free(render);

	return 0;
}
