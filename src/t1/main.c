#include "lrender.h"

int main(void)
{
	LRender* render = LRender_create();
	LRenderCamera* camera = render->camera;

	LRenderScene* scene = LRenderScene_create();

	LRenderNode* light1 = LRenderNode_create(LRENDER_NODE_DIRECT_LIGHT);
	LRenderNode_set_position(light1, 0.0f, 2.0f, -50.0f);
	LRenderScene_append_node(scene, light1);

	LRenderNode* node1 = LRenderNode_create(LRENDER_NODE_TESTBOX);
	LRenderNode_set_position(node1, 0.0f, 40.0f, -1000.0f);
	LRenderNode_set_rotation(node1, 0.0f, 30.0f, 0.0f);
	LRenderScene_append_node(scene, node1);

	LRenderNode* node2 = LRenderNode_create(LRENDER_NODE_TESTBOX);
	LRenderNode_set_position(node2, -100.0f, 0.0f, -500.0f);
	LRenderNode_set_rotation(node2, 0.0f, 30.0f, 50.0f);
	LRenderScene_append_node(scene, node2);


	LRenderScene_wait_load(scene);

	sleep(1);
	LRender_draw(render, scene);
	sleep(2);

	LRenderScene_free(scene);
	LRender_free(render);

	return 0;
}
