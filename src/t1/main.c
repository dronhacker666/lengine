#include "lrender.h"

int main(void)
{
	LRender* render = LRender_create();
	LRenderCamera* camera = render->camera;

	LRenderScene* scene = LRenderScene_create();

	LRenderNode* light1 = LRenderNode_create(LRENDER_NODE_DIRECT_LIGHT);
	LRenderNode_set_position(light1, 0.0f, 2.0f, -10.0f);
	LRenderScene_append_node(scene, light1);

	LRenderNode* node1 = LRenderNode_create(LRENDER_NODE_TESTBOX);
	LRenderNode_set_position(node1, 0.0f, 2.0f, -10.0f);
	LRenderScene_append_node(scene, node1);

	LRenderNode* node2 = LRenderNode_create(LRENDER_NODE_TESTBOX);
	LRenderNode_set_position(node2, 0.0f, -2.0f, -10.0f);
	LRenderScene_append_node(scene, node2);


	LRenderScene_wait_load(scene);


	LRender_draw(render, scene);

	sleep(2);

	LRenderScene_free(scene);
	LRender_free(render);

	return 0;
}
