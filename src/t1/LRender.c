#include "lrender.h"

#ifdef _WIN32

#elif __linux
	#include <dlfcn.h>
	#include <X11/X.h>
	#include <X11/Xlib.h>
#endif

static bool _create_opengl_context(LRender*, unsigned, unsigned);
static void _free_opengl_context(LRender*);
static void _swap_buffers(LRender*);
static void _init_render_to_screen(void);
static void _render_to_screen(LRender*, LRenderTarget*);

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

GLuint shader_program;
LRenderShader* ubershader;

LRender* LRender_create(void)
{
	info(L"Init Render");

	LRender* render = calloc(1, sizeof(LRender));

	_create_opengl_context(render, 800, 600);
	initOpenGLExt();
	print_opengl_info();

	render->camera = LRenderCamera_create();
	render->target = LRenderTarget_create(800, 600);

	//LRenderCamera_use_shader(render->camera, LRenderShader_create_from_file(""));

	info(L"Compile ubershader");

	ubershader = LRenderShader_create_from_file("shader/ubershader");

	shader_program = ubershader->program;

	_init_render_to_screen();

	return render;
}

void LRender_free(LRender* render)
{
	info(L"Free Render");
	LRenderShader_free(ubershader);
	LRenderCamera_free(render->camera);
	_free_opengl_context(render);
	free(render);
}

void LRender_draw(LRender* render, LRenderScene* scene)
{
	LRenderNode** node;
	array_rewind(scene->predraw_node_list);
	while((node = array_next(scene->predraw_node_list))){
		//LRenderNode_predraw(*node, render, scene);
	}

	LRenderCamera_rasterization_scene(render->camera, scene, render->target);

	_render_to_screen(render, render->target);

	_swap_buffers(render);
}


static GLuint VBO;
static GLuint VAO;
static LRenderShader* shader;

static void _init_render_to_screen(void)
{
	const float vertexes[][4] = {
		{-1.0f, 1.0f,  0.0f,1.0f},
		{ 1.0f, 1.0f,  1.0f,1.0f},
		{ 1.0f,-1.0f,  1.0f,0.0f},
		{-1.0f,-1.0f,  0.0f,0.0f},
	};

	shader = LRenderShader_create_from_file("shader/finish");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);


	GLint iPosition = glGetAttribLocation(shader->program, "iPosition");
	glVertexAttribPointer(iPosition, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
	glEnableVertexAttribArray(iPosition);

	GLint iTexCoord = glGetAttribLocation(shader->program, "iTexCoord");
	glVertexAttribPointer(iTexCoord, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (const GLvoid*)(2*sizeof(float)) );
	glEnableVertexAttribArray(iTexCoord);

	//glUniform1i(glGetUniformLocation(shader->program, "iTex0") , 0 /*GL_TEXTURE0*/);
}

static void _render_to_screen(LRender* render, LRenderTarget* target)
{
	glUseProgram(shader->program);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_DEPTH_TEST);


	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, target->depth);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

static bool _create_opengl_context(LRender* render, unsigned width, unsigned height)
{
#ifdef _WIN32

#elif __linux
	XSetWindowAttributes swa;

	GLint attr[] = {
		GLX_RGBA,
		GLX_DEPTH_SIZE, 24,
		GLX_DOUBLEBUFFER,
	None};

	render->display = XOpenDisplay(NULL);
	render->root = DefaultRootWindow(render->display);

	render->vi = glXChooseVisual(render->display, 0, attr);

	swa.colormap = XCreateColormap(render->display, render->root, render->vi->visual, AllocNone);
	swa.event_mask = ExposureMask | KeyPressMask;

	render->window = XCreateWindow(
		render->display,
		render->root,
		0, 0,
		width, height,
		0,
		render->vi->depth,
		InputOutput,
		render->vi->visual,
		CWColormap | CWEventMask,
		&swa
	);

	XMapWindow(render->display, render->window);
	XStoreName(render->display, render->window, "VERY SIMPLE APPLICATION");

	render->opengl_context = glXCreateContext(render->display, render->vi, NULL, GL_TRUE);
	glXMakeCurrent(render->display, render->window, render->opengl_context);

	return true;
#endif
}

static void _free_opengl_context(LRender* render)
{
#ifdef _WIN32

#elif __linux
	glXMakeCurrent(render->display, None, NULL);
	glXDestroyContext(render->display, render->opengl_context);
	XDestroyWindow(render->display, render->window);
	XCloseDisplay(render->display);
#endif
}

static void _swap_buffers(LRender* render)
{
#ifdef _WIN32

#elif __linux
	glXSwapBuffers(render->display, render->window);
#endif
}
