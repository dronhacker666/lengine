#include "lrender.h"

LRenderCamera* LRenderCamera_create(void)
{
	LRenderCamera* camera = calloc(1, sizeof(LRenderCamera));

	camera->fov = 45.0f;
	camera->znear = 1.0f;
	camera->zfar = 3000.0f;

	return camera;
}

void LRenderCamera_free(LRenderCamera* camera)
{
	free(camera);
}

void LRenderCamera_rasterization_scene(LRenderCamera* camera, LRenderScene* scene, LRenderTarget* target)
{
	glClearDepth(1.0f);
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	gen_perspective_mat4x4(
		camera->view_matrix,
		camera->fov,
		(float)target->width / (float)target->height,
		camera->znear,
		camera->zfar
	);

	glUseProgram(shader_program);
	glBindFramebuffer(GL_FRAMEBUFFER, target->FBO);

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	



/*	float aspectRatio = (float)camera->viewport.width / (float)camera->viewport.height;
	ERenderMatrix.perspective4f(projectionMatrix, 45.0f, aspectRatio, 0.01f, 500.0f);

	ERenderMatrix.translation4f(translationView, camera->position.x, camera->position.y, camera->position.z);
	ERenderMatrix.rotation4f(rotationView, camera->rotation.x, camera->rotation.y, camera->rotation.z);
	ERenderMatrix.mul4f(rotationView, rotationView, translationView);
	ERenderMatrix.mul4f(viewProjectionMatrix, projectionMatrix, rotationView);*/

	
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "viewMatrix"), 1, GL_TRUE, (const GLfloat*)camera->view_matrix);
	
	LRenderNode** node;
	array_rewind(scene->draw_node_list);
	while((node = array_next(scene->draw_node_list))){
		LRenderNode_draw(*node);
	}

	glDisable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
