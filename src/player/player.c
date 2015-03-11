#include <lengine.h>
#include <locale.h>

LENode* le_scene_load(FILE* fp, LENode* root)
{
	wchar_t tok[1024];
	wchar_t tok2[1024];
	LENode* node;

	while(fgettokwcs(fp, L"A-z", tok)){
		node = le_node_create(tok);
		le_node_append_child(root, node);
		
		if(fgettokwcs(fp, L"(", NULL)){
			while(fgettokwcs(fp, L"A-z", tok)){
				if(fgettokwcs(fp, L":", NULL)){
					if(fgettokwcs(fp, L"A-z0-9#.+-/:A-яЁё", tok2)){
						le_node_set_attribute(node, tok, (wcslen(tok2)+1)*sizeof(wchar_t), &tok2);
					}
				}
				if(fgettokwcs(fp, L")", NULL)) break;
			}
		}

		if(fgettokwcs(fp, L"{", NULL)){
			le_scene_load(fp, node);
			fgettokwcs(fp, L"}", NULL);
		}
	}

}

int main(void)
{
	setlocale(LC_ALL, "ru_RU.UTF8");

	LEngine engine;
	le_init(&engine);

	FILE* fp = fopen("../res/test.scene", "rb");

	le_scene_load(fp, engine.root);
	fclose(fp);

	le_load_module(&engine, L"test");

	while(le_run(&engine)){}

	return 0;
}
