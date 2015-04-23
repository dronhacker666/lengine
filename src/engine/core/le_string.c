#include "le_string.h"

static int _read_for (FILE* fp, int(*match)(wchar_t), wchar_t* buffer, int ret)
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

	while(!feof(fp)){
		if(!match(c=fgetwc(fp))){
			break;
		}
		*cur++ = c;
	}
	if(ret){
		ungetwc(c, fp);
	}

	if(cur==buffer){
		return 0;
	}else{
		*cur++ = L'\0';
		return 1;
	}
}


int fgettokwcs(FILE* fp, const wchar_t* allow, wchar_t* buffer)
{
	int match(wchar_t c){
		return wcinrange(c, allow);
	}
	return _read_for(fp, match, buffer, 1);
}


int fgettokwcsn(FILE* fp, const wchar_t* stop, wchar_t* buffer)
{
	int match(wchar_t c){
		return !wcinrange(c, stop);
	}
	return _read_for(fp, match, buffer, 0);
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
