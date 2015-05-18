#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

#include "obj.h"

typedef float vec3[3];
typedef float vec2[2];

typedef struct {
	vec3 v;
	vec2 vt;
} vertex_t;

typedef struct {
	size_t length;
	size_t element_size;
	size_t alloc;
	void* mem;
} array_t;

static array_t* array_create(size_t element_size, size_t init_length)
{
	array_t* a = malloc(sizeof(array_t));
	a->length = 0;
	a->alloc = init_length;
	a->element_size = element_size;
	a->mem = malloc(a->element_size*a->alloc);
	return a;
}

static void array_free(array_t* a)
{
	free(a->mem);
	free(a);
}

static void array_push(array_t* a, void* ptr)
{
	if(a->alloc<=a->length){
		a->alloc += 128;
		a->mem = realloc(a->mem, a->element_size*a->alloc);
	}
	memcpy(a->mem+(a->length*a->element_size), ptr, a->element_size);
	a->length++;
}

obj_t* obj_load(const char* file_name)
{
	regmatch_t match[13];
	regex_t reg_mtllib; regcomp(&reg_mtllib, "^mtllib (.+)\n", REG_EXTENDED|REG_ICASE);
	regex_t reg_v; regcomp(&reg_v, "^v\\s+(-?+[0-9]+\\.[0-9]+) (-?+[0-9]+\\.[0-9]+) (-?+[0-9]+\\.[0-9]+)", REG_EXTENDED|REG_ICASE);
	regex_t reg_vt; regcomp(&reg_vt, "^vt (-?+[0-9]+\\.[0-9]+) (-?+[0-9]+\\.[0-9]+)", REG_EXTENDED|REG_ICASE);
	regex_t reg_f4; regcomp(&reg_f4, "^f ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)? ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)? ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)? ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)?", REG_EXTENDED|REG_ICASE);
	regex_t reg_f3; regcomp(&reg_f3, "^f ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)? ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)? ([0-9]+)\\/?([0-9]+)?\\/?([0-9]+)?", REG_EXTENDED|REG_ICASE);

	array_t* vertex = array_create(sizeof(vertex_t), 1024);
	array_t* v = array_create(sizeof(vec3), 1024);
	array_t* vt = array_create(sizeof(vec2), 1024);

	FILE* fp = fopen(file_name, "r");

	char buff[1024];
	while(fgets(buff, 1024, fp)!=NULL){

		if(buff[0]=='#') continue;

		if(regexec(&reg_mtllib, buff, 2, match, 0)==0){

			buff[match[1].rm_eo] = '\0';

			printf("%s\n", buff + match[1].rm_so);
			continue;
		}

		if(regexec(&reg_v, buff, 4, match, 0)==0){
			buff[match[1].rm_eo] = '\0';
			buff[match[2].rm_eo] = '\0';
			buff[match[3].rm_eo] = '\0';
			vec3 _v = {
				atof(buff + match[1].rm_so),
				atof(buff + match[2].rm_so),
				atof(buff + match[3].rm_so)
			};

			array_push(v, &_v);
			continue;
		}

		if(regexec(&reg_vt, buff, 3, match, 0)==0){
			buff[match[1].rm_eo] = '\0';
			buff[match[2].rm_eo] = '\0';
			vec2 _vt = {
				(atof(buff + match[1].rm_so)+1.0f)*0.5f,
				(atof(buff + match[2].rm_so)+1.0f)*0.5f
			};
			array_push(vt, &_vt);
			continue;
		}

		if(regexec(&reg_f4, buff, 13, match, 0)==0){
			vertex_t _vertex[4];
			int i;
			for(i=0; i<4; i++){
				if(match[i*3+1].rm_eo>-1){
					buff[match[i*3+1].rm_eo] = '\0';
					memcpy(&_vertex[i].v, ((vec3*)v->mem)[atoi(buff + match[i*3+1].rm_so)-1], sizeof(vec3));
				}
				if(match[i*3+2].rm_eo>-1){
					buff[match[i*3+2].rm_eo] = '\0';
					memcpy(&_vertex[i].vt, ((vec2*)v->mem)[atoi(buff + match[i*3+2].rm_so)-1], sizeof(vec2));
				}
			}

			array_push(vertex, &_vertex[0]);
			array_push(vertex, &_vertex[1]);
			array_push(vertex, &_vertex[2]);
			array_push(vertex, &_vertex[2]);
			array_push(vertex, &_vertex[3]);
			array_push(vertex, &_vertex[0]);

			continue;
		}

		if(regexec(&reg_f3, buff, 10, match, 0)==0){
			vertex_t _vertex[3];
			int i;
			for(i=0; i<3; i++){
				if(match[i*3+1].rm_eo>-1){
					buff[match[i*3+1].rm_eo] = '\0';
					memcpy(&_vertex[i].v, ((vec3*)v->mem)[atoi(buff + match[i*3+1].rm_so)-1], sizeof(vec3));
				}
				if(match[i*3+2].rm_eo>-1){
					buff[match[i*3+2].rm_eo] = '\0';
					memcpy(&_vertex[i].vt, ((vec2*)v->mem)[atoi(buff + match[i*3+2].rm_so)-1], sizeof(vec2));
				}
			}
			array_push(vertex, &_vertex[0]);
			array_push(vertex, &_vertex[1]);
			array_push(vertex, &_vertex[2]);

			continue;
		}
	}

	fclose(fp);
	array_free(v);
	array_free(vt);

	obj_t* res = malloc(sizeof(obj_t));
	res->count = vertex->length;
	res->data = vertex->mem;
	free(vertex);

	return res;
}

void obj_free(obj_t* obj)
{
	free(obj->data);
	free(obj);
}
