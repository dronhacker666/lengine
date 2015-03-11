#include <lengine.h>

void renderTree(LENode*, int);


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


void renderTree(LENode* node, int depth)
{
	LENode* cur = node;
	while(cur){

		int i; for(i=0;i<depth;i++) wprintf(L"\t");

		wprintf(L"%ls", cur->tag_name);

		LENodeAttribute* attr = cur->attributes;
		if(attr){
			wprintf(L" (\n");
			while(attr){
				for(i=0;i<depth+1;i++) wprintf(L"\t");
				wprintf(L"%ls: %ls\n", attr->name, attr->value);
				attr = attr->next;
			}
			for(i=0;i<depth;i++) wprintf(L"\t");
			wprintf(L")");
		}

		if(cur->length){
			wprintf(L" {\n");
			renderTree(cur->children[0], depth+1);

			int i; for(i=0;i<depth;i++) wprintf(L"\t");
			wprintf(L"}");
		}

		wprintf(L"\n");
		cur = cur->next;
	}
}
