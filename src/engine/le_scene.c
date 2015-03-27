#include "le_scene.h"

static LENode* _le_scene_load(FILE* fp, LENode* root)
{
	wchar_t tok[1024];
	wchar_t tok2[1024];
	wchar_t tok3[1024];
	LENode* node;

	while(fgettokwcs(fp, L"A-z", tok)){
		node = le_node_create(tok);
		le_node_append_child(root, node);
		
		if(fgettokwcs(fp, L"(", NULL)){
			while(fgettokwcs(fp, L"A-z", tok)){
				if(fgettokwcs(fp, L":", NULL)){
					if(fgettokwcs(fp, L"\"\'", tok3)){
						fgettokwcsn(fp, tok3, tok2);
						le_node_set_attribute(node, tok, (wcslen(tok2)+1)*sizeof(wchar_t), &tok2);
					}else{
						if(fgettokwcs(fp, L"A-z0-9#.+-!?&/:A-яЁё", tok2)){
							le_node_set_attribute(node, tok, (wcslen(tok2)+1)*sizeof(wchar_t), &tok2);
						}
					}
				}
				if(fgettokwcs(fp, L")", NULL)) break;
			}
		}

		if(fgettokwcs(fp, L"{", NULL)){
			_le_scene_load(fp, node);
			fgettokwcs(fp, L"}", NULL);
		}
	}
}

LENode* le_scene_load(const char* file_name, LENode* node)
{
	FILE* fp = fopen(file_name, "rb");
	_le_scene_load(fp, node);
	fclose(fp);
}


/*

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

 */
