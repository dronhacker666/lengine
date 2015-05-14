#include "LRenderShader.h"

static GLuint default_vertex_shader = 0;
static GLuint default_fragment_shader = 0;

static GLuint _compile_shader(GLenum, const char*);
static GLuint _compile_from_file_shader(GLenum, const char*);
static bool _validate(LRenderShader*);
static bool _link_program(LRenderShader*);
static bool _set_shader(LRenderShader*, GLenum, GLuint);

/**
 * [LRenderShader_create description]
 * @return  [description]
 */
LRenderShader* LRenderShader_create(void)
{
	LRenderShader* shader = calloc(1, sizeof(LRenderShader));
	shader->program = glCreateProgram();
	shader->vertex = default_vertex_shader;
	shader->fragment = default_fragment_shader;

	if(_link_program(shader)){
		return shader;
	}else{
		LRenderShader_free(shader);
		return NULL;
	}
}

/**
 * [LRenderShader_free description]
 * @param shader [description]
 */
void LRenderShader_free(LRenderShader* shader)
{
	glDeleteProgram(shader->program);
	free(shader);
}

/**
 * [LRenderShader_use_as_default description]
 * @param  type      [description]
 * @param  file_name [description]
 * @return           [description]
 */
bool LRenderShader_use_as_default(GLenum type, const char* file_name)
{
	GLuint* target;
	switch(type){
		case GL_FRAGMENT_SHADER: target = &default_fragment_shader; break;
		case GL_VERTEX_SHADER: target = &default_vertex_shader; break;
		default: return false;
	}

	*target = _compile_from_file_shader(type, file_name);
	return *target ? true : false;
}


bool LRenderShader_load_default(LRenderShader* shader, GLenum type)
{
	switch(type){
		case GL_FRAGMENT_SHADER:
			_set_shader(shader, type, default_fragment_shader);
		break;
		case GL_VERTEX_SHADER:
			_set_shader(shader, type, default_vertex_shader);
		break;
		default: return false;
	}
	return _link_program(shader);
}

bool LRenderShader_load(LRenderShader* shader, GLenum type, const char* file_name)
{
	GLuint id = _compile_from_file_shader(type, file_name);
	if(id){
		if(_set_shader(shader, type, id)){
			return _link_program(shader);
		}
	}
	return false;
}

static bool _set_shader(LRenderShader* shader, GLenum type, GLuint id)
{
	switch(type){
		case GL_FRAGMENT_SHADER:
			glDetachShader(shader->program, shader->fragment);
			glDeleteShader(shader->fragment);
			shader->fragment = id;
		break;
		case GL_VERTEX_SHADER:
			glDetachShader(shader->program, shader->vertex);
			glDeleteShader(shader->vertex);
			shader->vertex = id;
		break;
		default: return false;
	}
	return true;
}



/**
 * [_link_program description]
 * @param  shader [description]
 * @return        [description]
 */
static bool _link_program(LRenderShader* shader)
{
	glUseProgram(shader->program);
	glAttachShader(shader->program, shader->vertex);
	glAttachShader(shader->program, shader->fragment);
	glLinkProgram(shader->program);

	glUseProgram(0);

	return _validate(shader);
}

/**
 * [_compile_from_file_shader description]
 * @param  type      [description]
 * @param  file_name [description]
 * @return           [description]
 */
static GLuint _compile_from_file_shader(GLenum type, const char* file_name)
{
	if(access(file_name, R_OK)==0){
		char* content = fgetcontent(file_name, NULL);
		GLuint shader = _compile_shader(type, content);
		free(content);
		return shader;
	}
	return 0;
}

/**
 * [_compile_shader description]
 * @param  type [description]
 * @param  src  [description]
 * @return      [description]
 */
static GLuint _compile_shader(GLenum type, const char* src)
{
	GLuint shader = glCreateShader(type);

	size_t src_length = strlen(src);

	glShaderSource(shader, 1, (const GLchar**)&src, (const GLint *)&src_length);
	glCompileShader(shader);

	GLint status;
	char buffer[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE){
		glGetShaderInfoLog(shader, 1024, 0, buffer);
		printf("Shader Error: %s\n", buffer);
		exit(1);
	}

	return shader;
}

/**
 * [_validate description]
 * @param  shader [description]
 * @return        [description]
 */
static bool _validate(LRenderShader* shader)
{
	char buffer[1024];
	GLint status;

	glGetProgramiv(shader->program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE){
		glGetProgramInfoLog(shader->program, 1024, 0, buffer);
		printf("Shader Program Link Error: %s\n", buffer);
		return false;
	}

	glValidateProgram(shader->program);
	glGetProgramiv(shader->program, GL_VALIDATE_STATUS, &status);
	if (status != GL_TRUE){
		glGetProgramInfoLog(shader->program, 1024, 0, buffer);
		printf("Shader Program Validate Error: %s\n", buffer);
		return false;
	}
	return true;
}
