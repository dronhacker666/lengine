#include "lengine.h"

#include <malloc.h>
#include <dlfcn.h>

LEngine* le_create(void)
{
	LEngine* engine = calloc(1, sizeof(LEngine));
	engine->root = le_node_create(L"ROOT");

	le_os_info(L"Engine init");
	le_init_modules(engine);

	return engine;
}

bool le_run(LEngine* engine)
{
	le_os_info(L"Engine run");
	sleep(1);
	return false;
}

void le_free(LEngine** engine)
{
	assert(*engine);

	le_node_free(&(*engine)->root);
	free(*engine);
	*engine = NULL;
	le_os_info(L"Engine end");
}

bool le_load_module(LEngine* engine, wchar_t* module_name)
{
	assert(engine);
	assert(module_name);

	wprintf(L"Load module \"%ls\"\n", module_name);

	char path[256];
	wchar_t tpath[256] = L"modules/";
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

	dlclose(lib);
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




bool le_add_system_handler(LEngine* engine, LESystemEventType event_type , LESystemHandler handler)
{
	handler(engine, 1);
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
