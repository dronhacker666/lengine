#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
#include <stdint.h>
#include <malloc.h>


typedef struct Node{
	struct Node* next;
	struct Node* prev;
	struct Node* parent;
	struct Node** children;
	size_t length;
	const char* tag_name;
} Node;

Node* le_node_create(const char*);
void le_node_append_child(Node*, Node*);



typedef struct {
	Node* root;
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


bool le_init(LEngine*);
bool le_run(LEngine*);
bool le_load_module(LEngine*, wchar_t*);
void le_push_module_msg(LEngine*, LEModule*, LEMsgType, void*);

#endif
