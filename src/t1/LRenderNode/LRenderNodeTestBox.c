#include "LRenderNodeTestBox.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include <stb/stb_image.h>

static GLuint tex = 0;

LRenderNodeTestBox* LRenderNodeTestBox_create(LRenderNode* node)
{
	node->need_draw = true;
	
	LRenderNodeTestBox* box = calloc(1, sizeof(LRenderNodeTestBox));

	const float s = 2.0f;
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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, box->VBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);


	if(!tex){

		int width, height, comp;
		FILE* fp = fopen("kamen.png", "rb");
		void* data = stbi_load_from_file(fp, &width, &height, &comp, 0);

		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		switch(comp){
			case 4:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
			default:
				printf("Bad texture format\n");
				abort();
			break;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);

		fclose(fp);
	}

	return box;
}

void LRenderNodeTestBox_free(LRenderNodeTestBox* box)
{
	free(box);
}

void LRenderNodeTestBox_draw(LRenderNodeTestBox* box)
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(glGetUniformLocation(program, "colorTex0") , 0);
	glActiveTexture(0);


	glBindVertexArray(box->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, box->VBO[0]);

	GLint iPosition = glGetAttribLocation(program, "iPosition");
	glVertexAttribPointer(iPosition, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(iPosition);

	GLint iTexCoord = glGetAttribLocation(program, "iTexCoord");
	glVertexAttribPointer(iTexCoord, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const GLvoid*)(3*sizeof(float)) );
	glEnableVertexAttribArray(iTexCoord);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}
