#ifndef _LENGINE_H_
#define _LENGINE_H_

#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdint.h>

#include "le_node.h"
#include "le_scene.h"

typedef struct {
	LENode* root;
} LEngine;

typedef enum {
	MSG_RUN,
	MSG_END,
} LEMsgType;

typedef struct {
	LEMsgType type;
	LEngine* engine;
	void* data;
} LEMsg;

typedef struct {
	void(*push_msg)(LEMsg*);
} LEModule;


LEngine* le_create(void);
bool le_run(LEngine* asdasfasd);
void le_free(LEngine**);

void le_init_modules(LEngine*);

typedef enum {
	LE_SYSTEM_EVENT_CREATE_NODE,
} LESystemEventType;

typedef void(LESystemHandler)(LEngine*, void*);

bool le_add_system_handler(LEngine*, LESystemEventType, LESystemHandler);



bool le_load_module(LEngine*, wchar_t*);
void le_push_module_msg(LEngine*, LEModule*, LEMsgType, void*);


bool le_os_load_file(const char*, char**, size_t*);

#endif
