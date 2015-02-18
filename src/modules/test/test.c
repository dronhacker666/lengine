#include <engine.h>

void renderTree(Node*, int);


void _receive_msg(LEMsg* msg)
{
	switch(msg->type){
		
		case MSG_RUN:
			wprintf(L"Module test run\n");
			renderTree(msg->engine->root, 0);
			break;

		case MSG_END:
			wprintf(L"Module test end\n");
			break;
	}
}


void renderTree(Node* node, int depth)
{
	int i; for(i=0;i<depth;i++) wprintf(L"|  ");

	if(node->length){
		wprintf(L"%s(%i):\n", node->tag_name, node->length);
		renderTree(node->children[0], depth+1);
	}else{
		wprintf(L"%s\n", node->tag_name);
	}

	if(node->next){
		renderTree(node->next, depth);
	}
}
