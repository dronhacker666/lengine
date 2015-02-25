#include <lengine.h>

LENode* le_scene_load(FILE* fp, LENode* root)
{
	int fgettok(FILE* fp, const char* allow, char* buffer){
		const char* skip = " \n\t\r";
		char c;

		if(buffer==NULL){
			static char _buffer[1024];
			buffer = _buffer;
		}

		char* cur = buffer;

		size_t start_pos = ftell(fp);

		int in_range(char ch, const char* range){
			do{
				if(*(range+1)=='-'){
					if(ch>=*range && ch<=*(range+2)) return 1;
					range+=2;
				}else{
					if(*range==ch) return 1;
				}
			}while(*range++);
			return 0;
		}

		while(in_range(fgetc(fp), skip)){}
		fseek(fp, -1, SEEK_CUR);

		while(!feof(fp)){
			c = fgetc(fp);
			if(!in_range(c, allow)) break;
			*cur++ = c;
		}
		fseek(fp, -1, SEEK_CUR);

		if(cur==buffer){
			fseek(fp, start_pos, SEEK_SET);
			return 0;
		}else{
			*cur++ = '\0';
			return 1;
		}
	}

	char tok[1024];
	char tok2[1024];
	LENode* node;

	while(fgettok(fp, "A-z", tok)){
		node = le_node_create(tok);
		le_node_append_child(root, node);

		if(fgettok(fp, "(", NULL)){
			while(fgettok(fp, "A-z", tok)){
				if(fgettok(fp, ":", NULL)){
					if(fgettok(fp, "A-z0-9", tok2)){
						le_node_set_attribute(node, tok, strlen(tok2), &tok2);
					}
				}
				fgettok(fp, ",", NULL);
				if(fgettok(fp, ")", NULL)) break;
			}
		}

		if(fgettok(fp, "{", NULL)){
			le_scene_load(fp, node);
			fgettok(fp, "}", NULL);
		}
	}

}

int main(void)
{
	LEngine engine;
	le_init(&engine);

	wprintf(L"%s\n", __FUNCTION__);

	FILE* fp = fopen("../res/test.scene", "rb");
	le_scene_load(fp, engine.root);
	fclose(fp);

	le_load_module(&engine, L"test");

	while(le_run(&engine)){}

	return 0;
}
