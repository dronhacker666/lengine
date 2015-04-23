#include "lrender.h"

LRenderCamera* LRenderCamera_create(void)
{
	LRenderCamera* camera = calloc(1, sizeof(LRenderCamera));

	camera->fov = 45.0f;
	camera->znear = 0.001f;
	camera->zfar = 500.0f;

	gen_perspective_mat4x4(camera->view_matrix, camera->fov, /*aspectRatio*/1.0f, camera->znear, camera->zfar);

	return camera;
}

void LRenderCamera_free(LRenderCamera* camera)
{
	free(camera);
}

void LRenderCamera_rasterization_scene(LRenderCamera* camera, LRenderScene* scene)
{
	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


/*	float aspectRatio = (float)camera->viewport.width / (float)camera->viewport.height;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	ERenderMatrix.translation4f(translationView, camera->position.x, camera->position.y, camera->position.z);
	ERenderMatrix.rotation4f(rotationView, camera->rotation.x, camera->rotation.y, camera->rotation.z);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);*/

	glUseProgram(shader_program);

	glUniformMatrix4fv(glGetUniformLocation(shader_program, "viewMatrix"), 1, GL_TRUE, (const GLfloat*)camera->view_matrix);
	
	LRenderNode** node;
	array_rewind(scene->draw_node_list);
	while((node = array_next(scene->draw_node_list))){
		LRenderNode_draw(*node);
	}
}
