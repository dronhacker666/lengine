#include "LRenderNodeTestBox.h"

LRenderNodeTestBox* LRenderNodeTestBox_create(LRenderNode* node)
{
	node->need_draw = true;
	
	LRenderNodeTestBox* box = calloc(1, sizeof(LRenderNodeTestBox));

	const float s = 1.0f;
	const float vertexes[][5] = {
		{-s, s, s,  0.0f,1.0f}, { s, s, s,  1.0f,1.0f}, { s,-s, s,  1.0f,0.0f}, {-s,-s, s,  0.0f,0.0f}, // front
		{ s, s,-s,  0.0f,1.0f}, {-s, s,-s,  1.0f,1.0f}, {-s,-s,-s,  1.0f,0.0f}, { s,-s,-s,  0.0f,0.0f}, // back
		{-s, s,-s,  0.0f,1.0f}, { s, s,-s,  1.0f,1.0f}, { s, s, s,  1.0f,0.0f}, {-s, s, s,  0.0f,0.0f}, // top
		{ s,-s,-s,  0.0f,1.0f}, {-s,-s,-s,  1.0f,1.0f}, {-s,-s, s,  1.0f,0.0f}, { s,-s, s,  0.0f,0.0f}, // bottom
		{-s, s,-s,  0.0f,1.0f}, {-s, s, s,  1.0f,1.0f}, {-s,-s, s,  1.0f,0.0f}, {-s,-s,-s,  0.0f,0.0f}, // left
		{ s, s, s,  0.0f,1.0f}, { s, s,-s,  1.0f,1.0f}, { s,-s,-s,  1.0f,0.0f}, { s,-s, s,  0.0f,0.0f}  // right
	};

	const uint32_t indices[] = {
		 0, 3, 1,  1, 3, 2, // front
		 4, 7, 5,  5, 7, 6, // back
		 8,11, 9,  9,11,10, // top
		12,15,13, 13,15,14, // bottom
		16,19,17, 17,19,18, // left
		20,23,21, 21,23,22  // right
	};

	glGenVertexArrays(1, &box->VAO);
	glBindVertexArray(box->VAO);

	glGenBuffers(2, box->VBO);

	glBindBuffer(GL_ARRAY_BUFFER, box->VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	GLint positionLocation = glGetAttribLocation(shader_program, "iPosition");
	glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(positionLocation);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box->VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	return box;
}

void LRenderNodeTestBox_free(LRenderNodeTestBox* box)
{
	free(box);
}

void LRenderNodeTestBox_draw(LRenderNodeTestBox* box)
{
	printf("draw box\n");

	float color[3] = {1.0, 0.0, 0.0};
	glUniform3fv(glGetUniformLocation(shader_program, "uColor"), 1, (const GLfloat*)&color);

	glBindVertexArray(box->VAO);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
}
