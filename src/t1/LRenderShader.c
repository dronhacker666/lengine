#include "LRenderShader.h"

#define SHADER_TYPE_COUNT 2
static struct _Parts {
	const char* sufix;
	GLuint type;
} parts[SHADER_TYPE_COUNT] = {
	{"fsh", GL_FRAGMENT_SHADER},
	{"vsh", GL_VERTEX_SHADER},
};

static GLuint _compile_shader(GLenum type, const char* src);

LRenderShader* LRenderShader_create(void)
{
	LRenderShader* shader = calloc(1, sizeof(LRenderShader));
	shader->program = glCreateProgram();
	return shader;
}

void LRenderShader_free(LRenderShader* shader)
{
	glDeleteProgram(shader->program);
	free(shader);
}

LRenderShader* LRenderShader_create_from_file(const char* file_name)
{
	LRenderShader* shader = LRenderShader_create();
	if(LRenderShader_from_file(shader, file_name)){
		return shader;
	}
	LRenderShader_free(shader);
	return NULL;
}

bool LRenderShader_from_file(LRenderShader* shader, const char* file_name)
{
	char full_name[1024];

	glUseProgram(shader->program);

	for(int i=0; i<SHADER_TYPE_COUNT; i++){
		sprintf(full_name, "%s.%s", file_name, parts[i].sufix);
		char* content = fgetcontent(full_name);

		GLuint shader_part= _compile_shader(parts[i].type, content);
		glAttachShader(shader->program, shader_part);
		glDeleteShader(shader_part);

		free(content);
	}

	//----------

	char buffer[1024];
	GLint status;

	glLinkProgram(shader->program);
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
