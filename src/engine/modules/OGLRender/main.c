#include <core/lengine.h>

static void on_create_node(LEngine* engine, void* _node)
{
	assert(engine);
	assert(_node);

	LENode* node = (LENode*)_node;
}

int OGLRender_init(LEngine* engine)
{
	le_os_info(L"Hello FROM OGLRender");


	le_add_system_handler(engine, LE_SYSTEM_EVENT_CREATE_NODE, &on_create_node);

	return 0;
}
