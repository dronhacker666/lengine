#include "LRenderNodeSprite.h"

LRenderNodeSprite* LRenderNodeSprite_create(LRenderNode* node)
{
	node->need_draw = true;

	LRenderNodeSprite* sprite = calloc(1, sizeof(LRenderNodeSprite));

	float mesh[9] = {
		-1.0f, -1.0f, -5.0f,
		0.0f,  1.0f, -5.0f,
		1.0f, -1.0f, -5.0f,
	};

	glGenVertexArrays(1, &sprite->VAO);
	glBindVertexArray(sprite->VAO);

	glGenBuffers(1, &sprite->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);

	GLint positionLocation = glGetAttribLocation(shader_program, "iPosition");
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
	glEnableVertexAttribArray(positionLocation);

	glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(float), mesh, GL_STATIC_DRAW);

	return sprite;
}

void LRenderNodeSprite_free(LRenderNodeSprite* sprite)
{
	free(sprite);
}

void LRenderNodeSprite_draw(LRenderNodeSprite* sprite)
{
	printf("draw sprite\n");

	glBindVertexArray(sprite->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, sprite->VBO);

	glUniform3fv(glGetUniformLocation(shader_program, "uColor"), 1, (const GLfloat*)&sprite->color);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void LRenderNodeSprite_set_color(LRenderNodeSprite* sprite, float r, float g, float b)
{
	sprite->color[0] = r;
	sprite->color[1] = g;
	sprite->color[2] = b;
}


bool LRenderNodeSprite_set_image(LRenderNodeSprite* sprite, const wchar_t* file_name)
{
	sprite->file_name = wcsdup(file_name);
}
