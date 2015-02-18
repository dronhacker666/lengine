#include <engine.h>

int main(void)
{
	LEngine engine;
	le_init(&engine);

	Node* html = le_node_create("HTML");
	Node* head = le_node_create("HEAD");
	Node* body = le_node_create("BODY");
	le_node_append_child(html, head);
	le_node_append_child(html, body);
	Node* subnode = le_node_create("ROOM");
		le_node_append_child(subnode, le_node_create("CAMERA"));
		le_node_append_child(subnode, le_node_create("LIGHT"));
	le_node_append_child(body, subnode);
	le_node_append_child(engine.root, html);


	le_load_module(&engine, L"test");

	while(le_run(&engine)){}


	return 0;
}
