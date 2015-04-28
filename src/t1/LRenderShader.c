#include "LRenderShader.h"

static GLuint _compile_shader(GLenum type, const char* src);


LRenderShader* LRenderShader_create(void)
{
	LRenderShader* shader = calloc(1, sizeof(LRenderShader));
	shader->program = glCreateProgram();
	return shader;
}

void LRenderShader_free(LRenderShader* shader)
{
	free(shader);
}

bool LRenderShader_from_file(LRenderShader* shader, const char* file_name)
{
	struct _Parts {
		const char* sufix;
		GLuint type;
	} parts[] = {
		{"fsh", GL_FRAGMENT_SHADER},
		{"vsh", GL_VERTEX_SHADER},
	};

	char full_name[1024];

	glUseProgram(shader->program);

	for(int i=0; i<sizeof(parts)/sizeof(struct _Parts); i++){
		sprintf(full_name, "%s.%s", file_name, parts[i].sufix);
		char* content = fgetcontent(full_name);

		glAttachShader(shader->program, _compile_shader(parts[i].type, content));

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
		exit(1);
	}

	glValidateProgram(shader->program);
	glGetProgramiv(shader->program, GL_VALIDATE_STATUS, &status);
	if (status != GL_TRUE){
		glGetProgramInfoLog(shader->program, 1024, 0, buffer);
		printf("Shader Program Validate Error: %s\n", buffer);
		exit(1);
	}	
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
