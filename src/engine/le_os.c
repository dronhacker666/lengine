#include <ref.h>

bool le_os_load_file(const char* filename, char** content, size_t* length)
{
	FILE* fp = fopen(filename, "rb");
	int size;
	if(fp==NULL){
		wprintf(L"Can't open file \"%s\"\n", filename);
		return false;
	}else{
		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		rewind(fp);
		*content = malloc( sizeof(char)*size+1 );
		if(*content==NULL){
			wprintf(L"%s\n", "No memory");
			return false;
		}
		fread(*content, sizeof(char)*size , 1, fp);

		(*content)[size] = '\0';

		if(length){
			*length = size;
		}
		fclose(fp);
	}
	return true;
}
