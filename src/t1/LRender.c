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
	free(render);
}

void LRender_draw(LRender* render, LRenderScene* scene, LRenderCamera* camera)
{
	LRenderNode** node;

	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


/*	float aspectRatio = (float)camera->viewport.width / (float)camera->viewport.height;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	ERenderMatrix.translation4f(translationView, camera->position.x, camera->position.y, camera->position.z);
	ERenderMatrix.rotation4f(rotationView, camera->rotation.x, camera->rotation.y, camera->rotation.z);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);*/

	glUseProgram(shader_program);

	Mat4x4 viewProjectionMatrix;

	float aspectRatio = (float)600 / (float)600;

	gen_perspective_mat4x4(viewProjectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	glUniformMatrix4fv(glGetUniformLocation(shader_program, "viewMatrix"), 1, GL_TRUE, (const GLfloat*)&viewProjectionMatrix);

	array_rewind(scene->geometry);
	while((node = array_next(scene->geometry))){
		LRenderNode_draw(*node);
	}


	swap_buffers();
}
