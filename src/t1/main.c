#include "lrender.h"

int main(void)
{
	LRender* render = LRender_create();
	LRenderCamera* camera = LRenderCamera_create();
		gen_identity_mat4x4(camera->projection);

	LRenderScene* scene = LRenderScene_create();

	LRenderNode* node1 = LRenderNode_create(LRENDER_NODE_TESTBOX);
	LRenderNode_set_position(node1, 0.0f, 2.0f, -10.0f);
	LRenderScene_append_node(scene, node1);

	LRenderNode* node2 = LRenderNode_create(LRENDER_NODE_TESTBOX);
	LRenderNode_set_position(node2, 0.0f, -2.0f, -10.0f);
	LRenderScene_append_node(scene, node2);


	LRenderScene_wait_load(scene);


	LRender_draw(render, scene, camera);

	sleep(2);

	LRenderCamera_free(camera);
	LRenderScene_free(scene);
	LRender_free(render);

	return 0;
}
