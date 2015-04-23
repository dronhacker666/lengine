#include "ref.h"
#include <time.h>

void le_os_log(const wchar_t* msg, LEOSLogType type)
{
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);

	char* type_str;
	switch(type){
		case LEOS_LOG_INFO:
			type_str = "INFO";
			break;
		case LEOS_LOG_WARNING:
			type_str = "WARNING";
			break;
		case LEOS_LOG_ERROR:
			type_str = "ERROR";
			break;
	}
	wprintf(L"[%s] [%i-%02i-%02i %02i:%02i:%02i] %ls\n",
		type_str,
		1900+tm->tm_year,
		tm->tm_mon+1,
		tm->tm_mday,
		tm->tm_hour,
		tm->tm_min,
		tm->tm_sec,
		msg
	);
}

void le_os_info(const wchar_t* msg)
{
	le_os_log(msg, LEOS_LOG_INFO);
}

void le_os_warning(const wchar_t* msg)
{
	le_os_log(msg, LEOS_LOG_WARNING);
}

void le_os_error(const wchar_t* msg)
{
	le_os_log(msg, LEOS_LOG_ERROR);
}


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
