GLuint shader_program;

static GLuint _compile_shader(GLenum type, const char* src)
{
	GLuint shader = glCreateShader(type);

	size_t src_length = strlen(src);

	const char* sources[] = {src};

	glShaderSource(shader, 1, (const GLchar**)sources, (const GLint *)&src_length);
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

static void ubershader()
{
	shader_program = glCreateProgram();

	GLuint vertex = _compile_shader(GL_VERTEX_SHADER, "\
		#version 130\n\
		uniform mat4 viewMatrix;\
		uniform mat4 modelMatrix;\
		in vec3 iPosition;\
		out vec2 screenPosition;\
		\
		void main(void)\
		{\
			gl_Position = viewMatrix * (modelMatrix * vec4(iPosition, 1.0));\
			screenPosition = gl_Position.xy;\
		}\
	");
	GLuint fragment = _compile_shader(GL_FRAGMENT_SHADER, "\
		#version 130\n\
		uniform vec3 uColor;\
		in vec2 screenPosition;\
		out vec4 color;\
		float screen_width = 600;\
		float screen_height = 600;\
		\
		void main(void)\
		{\
			color = vec4(uColor, 1.0);\
		}\
	");

	glAttachShader(shader_program, vertex);
	glAttachShader(shader_program, fragment);

	char buffer[1024];
	GLint status;

	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE){
		glGetProgramInfoLog(shader_program, 1024, 0, buffer);
		printf("Shader Program Link Error: %s\n", buffer);
		exit(1);
	}

	glValidateProgram(shader_program);
	glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &status);
	if (status != GL_TRUE){
		glGetProgramInfoLog(shader_program, 1024, 0, buffer);
		printf("Shader Program Validate Error: %s\n", buffer);
		exit(1);
	}
}
