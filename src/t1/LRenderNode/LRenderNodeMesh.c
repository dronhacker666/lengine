#include "LRenderNodeMesh.h"
#include "../decoders/obj.h"

LRenderNodeMesh* LRenderNodeMesh_create(LRenderNode* node)
{
	node->need_draw = true;
	LRenderNodeMesh* mesh = calloc(1, sizeof(LRenderNodeMesh));

	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);

	glGenBuffers(1, &mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

	glBindVertexArray(0);

	return mesh;
}

void LRenderNodeMesh_free(LRenderNodeMesh* mesh)
{
	free(mesh);
}

void LRenderNodeMesh_draw(LRenderNodeMesh* mesh)
{
	GLint program;
	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	glBindVertexArray(mesh->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

	GLint iPosition = glGetAttribLocation(program, "iPosition");
	glVertexAttribPointer(iPosition, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(iPosition);

	GLint iTexCoord = glGetAttribLocation(program, "iTexCoord");
	glVertexAttribPointer(iTexCoord, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (const GLvoid*)(3*sizeof(float)) );
	glEnableVertexAttribArray(iTexCoord);

	glDrawArrays(GL_TRIANGLES, 0, mesh->vertex_count);
	glBindVertexArray(0);
}

void LRenderNodeMesh_load(LRenderNodeMesh* mesh, const char* file_name)
{
	obj_t* obj = obj_load(file_name);
	mesh->vertex_count = obj->count;

	printf("load %i vertext\n", mesh->vertex_count);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float[5])*obj->count, obj->data, GL_STATIC_DRAW);
	obj_free(obj);
}
