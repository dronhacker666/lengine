#include <le_node.h>

/**
 * [le_node_create description]
 * @param  tagName [description]
 * @return         [description]
 */
LENode* le_node_create(const wchar_t* tag_name)
{
	static unsigned _id = 1;
	LENode* node = calloc(1, sizeof(LENode));
	node->id = _id++;
	node->tag_name = wcstolower(wcsdup(tag_name));
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


LENodeAttribute* le_node_get_attribute(LENode* node, const wchar_t* _name)
{
	assert(node);
	assert(_name);

	wchar_t* name = wcstolower(wcsdup(_name));

	LENodeAttribute* cur = node->attributes;
	while(cur){
		if( wcscmp(cur->name, name)==0 ){
			return cur;
		}
		cur = cur->next;
	};

	free(name);

	return NULL;
}

void le_node_set_attribute(LENode* node, const wchar_t* name, size_t size, void* data)
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

		attr->name = wcstolower(wcsdup(name));
	}

	if(attr->value){
		free(attr->value);
	}

	attr->value = malloc(size);
	memcpy(attr->value, data, size);
}
