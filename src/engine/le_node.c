#include <le_node.h>

/**
 * [le_node_create description]
 * @param  tagName [description]
 * @return         [description]
 */
LENode* le_node_create(const char* tag_name)
{
	LENode* node = calloc(1, sizeof(LENode));
	node->tag_name = strdup(tag_name);
	return node;
}

/**
 * [le_node_append_child description]
 * @param parent [description]
 * @param child  [description]
 */
void le_node_append_child(LENode* parent, LENode* child)
{
	assert(parent);
	assert(child);

	parent->length++;
	parent->children = realloc(parent->children, sizeof(LENode*)*parent->length);
	parent->children[parent->length-1] = child;

	if(parent->length>1){
		parent->children[parent->length-2]->next = child;
		child->prev = parent->children[parent->length-2];
	}

	child->parent = parent;
}


LENodeAttribute* le_node_get_attribute(LENode* node, const char* name)
{
	assert(node);
	assert(name);

	LENodeAttribute* cur = node->attributes;
	while(cur){
		if( strcmp(cur->name, name)==0 ){
			return cur;
		}
		cur = cur->next;
	};

	return NULL;
}

void le_node_set_attribute(LENode* node, const char* name, size_t size, void* data)
{
	assert(node);
	assert(name);


	LENodeAttribute* attr = le_node_get_attribute(node, name);


	if(!attr){
		attr = calloc(1, sizeof(LENodeAttribute));
		if(node->attributes){
			attr->next = node->attributes;
		}
		node->attributes = attr;

		attr->name = strdup(name);
	}


	if(attr->value){
		free(attr->value);
	}

	attr->value = malloc(size);
	memcpy(attr->value, data, size);
}
