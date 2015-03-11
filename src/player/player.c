#include <lengine.h>
#include <locale.h>

LENode* le_scene_load(FILE* fp, LENode* root)
{

	int fgettok(FILE* fp, const wchar_t* allow, wchar_t* buffer){
		const wchar_t* skip = L" \n\t\r";
		wchar_t c;

		if(buffer==NULL){
			static wchar_t _buffer[1024];
			buffer = _buffer;
		}

		wchar_t* cur = buffer;

		int in_range(wchar_t ch, const wchar_t* range){
			do{
				if(*(range+1)==L'-'){
					if(ch>=*range && ch<=*(range+2)) return 1;
					range+=2;
				}else{
					if(*range==ch) return 1;
				}
			}while(*range++);
			return 0;
		}

		while(in_range(c=fgetwc(fp), skip)){}
		ungetwc(c, fp);

		while(!feof(fp) && in_range(c=fgetwc(fp), allow)){
			*cur++ = c;
		}
		ungetwc(c, fp);

		if(cur==buffer){
			return 0;
		}else{
			*cur++ = L'\0';
			return 1;
		}
	}

	wchar_t tok[1024];
	wchar_t tok2[1024];
	LENode* node;

	while(fgettok(fp, L"A-z", tok)){
		node = le_node_create(tok);
		le_node_append_child(root, node);
		
		wprintf(L"Create node %ls\n", tok);
		

		if(fgettok(fp, L"(", NULL)){
			while(fgettok(fp, L"A-z", tok)){
				if(fgettok(fp, L":", NULL)){
					if(fgettok(fp, L"A-z0-9#.+-/:A-яЁё", tok2)){
						le_node_set_attribute(node, tok, (wcslen(tok2)+1)*sizeof(wchar_t), &tok2);
						wprintf(L"\tSet attibute %ls %ls\n", tok, tok2);
					}
				}
				if(fgettok(fp, L")", NULL)) break;
			}
		}

		if(fgettok(fp, L"{", NULL)){
			le_scene_load(fp, node);
			fgettok(fp, L"}", NULL);
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
