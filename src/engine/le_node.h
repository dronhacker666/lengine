#ifndef _LE_NODE_H_
#define _LE_NODE_H_

#include <ref.h>

typedef struct LENodeAttribute {
	const wchar_t* name;
	void* value;
	struct LENodeAttribute* next;
} LENodeAttribute;

typedef struct LENode {
	unsigned int id;
	struct LENode* next;
	struct LENode* prev;
	struct LENode* parent;
	struct LENode** children;
	size_t length;
	const wchar_t* tag_name;
	LENodeAttribute* attributes;
} LENode;

LENode* le_node_create(const wchar_t*);
void le_node_append_child(LENode*, LENode*);

LENodeAttribute* le_node_get_attribute(LENode*, const wchar_t*);
void le_node_set_attribute(LENode*, const wchar_t*, size_t, void*);


#endif
