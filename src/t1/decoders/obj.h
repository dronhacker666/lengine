#ifndef _DECODER_OBJ_H_
#define _DECODER_OBJ_H_

typedef struct {
	size_t count;
	float* data;
} obj_t;

obj_t* obj_load(const char*);
void obj_free(obj_t*);

#endif
