#include <core/lengine.h>
#include <locale.h>

int main(void)
{
	setlocale(LC_ALL, "ru_RU.UTF8");

	LEngine* engine = le_create();
	le_scene_load("../res/test.scene", engine->root);

	while(le_run(engine)){}

	le_free(&engine);

	return 0;
}
