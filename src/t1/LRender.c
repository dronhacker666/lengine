#include "lrender.h"

#ifdef _WIN32
	#include "windows/LRender.c"
#elif __linux
	#include "linux/LRender.c"
#endif

#include "shader/ubershader.c"

static void print_opengl_info(void)
{
	GLint maj, min;
	GLint texture_units;
	GLint max_texture_size;
	glGetIntegerv(GL_MAJOR_VERSION, &maj);
	glGetIntegerv(GL_MINOR_VERSION, &min);
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);

	printf("OpenGL gApi context information:\n");

	printf("Avaible OpengGL  : %i.%i\n", maj, min);
	printf("Renderer         : %s\n", (char*)glGetString(GL_RENDERER));
	printf("Version          : %s\n", (char*)glGetString(GL_VERSION));
	printf("GLSL version     : %s\n", (char*)glGetString(GL_SHADING_LANGUAGE_VERSION));

	printf("Texture units    : %i\n", texture_units);
	printf("Max texture size : %i\n", max_texture_size);
}


LRender* LRender_create(void)
{
	LRender* render = calloc(1, sizeof(LRender));

	render->camera = LRenderCamera_create();
	render->camera->target = LRenderTarget_create(LRENDER_TARGET_SCREEN, 800, 600);

	info(L"Init Render");

	init_opengl_context();
	print_opengl_info();

	info(L"Init OpenGL ext");
	initOpenGLExt();

	info(L"Compile ubershader");
	ubershader();

	glEnable(GL_DEPTH_TEST);

	return render;
}

void LRender_free(LRender* render)
{
	info(L"Free Render");
	
	free_opengl_context();

	LRenderTarget_free(render->camera->target);
	LRenderCamera_free(render->camera);
	free(render);
}

void LRender_draw(LRender* render, LRenderScene* scene)
{
	// Prepare lights

	LRenderNode** node;

	array_rewind(scene->predraw_node_list);
	while((node = array_next(scene->predraw_node_list))){
		LRenderNode_predraw(*node, scene);
		// add light to light list
	}

	LRenderCamera_rasterization_scene(render->camera, scene);

	swap_buffers();
}
