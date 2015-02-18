#include <engine.h>
#include <dlfcn.h>

bool le_init(LEngine* engine)
{
	engine->root = le_node_create("ROOT");

	wprintf(L"Engine init\n");
}

bool le_run(LEngine* engine)
{
	wprintf(L"Engine run\n");
	return false;
}

bool le_load_module(LEngine* engine, wchar_t* module_name)
{
	wprintf(L"Load module \"%ls\"\n", module_name);

	char path[256];
	wchar_t tpath[256] = L"../src/modules/";
	wcscat(tpath, module_name);
	wcscat(tpath, L"/");
	wcscat(tpath, module_name);
	wcscat(tpath, L".module");

	wcstombs(path, tpath, sizeof(path));

	void* lib = dlopen(path, RTLD_LAZY);
	if(!lib){
		wprintf(L"DL error %s\n", dlerror());
		exit(1);
	}

	LEModule* module = malloc(sizeof(LEModule));

	module->push_msg = dlsym(lib, "_receive_msg");
	if(!module->push_msg){
		wprintf(L"DL error %s\n", dlerror());
		exit(-1);
	}

	le_push_module_msg(engine, module, MSG_RUN, NULL);

	//dlclose(lib);
}


void le_push_module_msg(LEngine* engine, LEModule* module, LEMsgType type, void* data)
{
	LEMsg msg = {
		engine: engine,
		type: type,
		data: data,
	};
	module->push_msg(&msg);
}


/**
 * [createNode description]
 * @param  tagName [description]
 * @return         [description]
 */
Node* le_node_create(const char* tag_name)
{
	Node* node = calloc(1, sizeof(Node));
	node->tag_name = tag_name;
	return node;
}

/**
 * [appendChild description]
 * @param parent [description]
 * @param child  [description]
 */
void le_node_append_child(Node* parent, Node* child)
{
	parent->length++;
	parent->children = realloc(parent->children, sizeof(Node*)*parent->length);
	parent->children[parent->length-1] = child;

	if(parent->length>1){
		parent->children[parent->length-2]->next = child;
		child->prev = parent->children[parent->length-2];
	}

	child->parent = parent;
}

// bool track_file(const char* file_name, void(*callback)(void))
// {
// 	struct stat buf;
// 	int timer;
// 	while(1){
// 		if(stat(file_name, &buf)!=0){
// 			return false;
// 		}
// 		if(timer != buf.st_mtime){
// 			callback();
// 		}
// 		timer = buf.st_mtime;
// 		//sleep(1);
// 	}
// }
