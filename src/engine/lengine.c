#include <lengine.h>

#include <malloc.h>
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
