#include <le_string.h>

int fgettokwcs(FILE* fp, const wchar_t* allow, wchar_t* buffer)
{
	const wchar_t* skip = L" \n\t\r";
	wchar_t c;

	if(buffer==NULL){
		static wchar_t _buffer[1024];
		buffer = _buffer;
	}

	wchar_t* cur = buffer;

	while(wcinrange(c=fgetwc(fp), skip)){}
	ungetwc(c, fp);

	while(!feof(fp) && wcinrange(c=fgetwc(fp), allow)){
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

int wcinrange(wchar_t ch, const wchar_t* range)
{
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

wchar_t* wcstolower(wchar_t* p){
	wchar_t* _p = p;
	do{
		*_p = towlower(*_p);
	}while(*_p++);
	return p;
}
