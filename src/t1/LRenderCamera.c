#include "lrender.h"

LRenderCamera* LRenderCamera_create(void)
{
	LRenderCamera* camera = calloc(1, sizeof(LRenderCamera));

	camera->fov = 45.0f;
	camera->znear = 0.01f;
	camera->zfar = 1000.0f;

	return camera;
}

void LRenderCamera_free(LRenderCamera* camera)
{
	free(camera);
}

void LRenderCamera_rasterization_scene(LRenderCamera* camera, LRenderScene* scene, LRenderTarget* target)
{
	Mat4x4 view_matrix;
	Mat4x4 translation_matrix;
	Mat4x4 rotation_matrix;

	gen_perspective_mat4x4(view_matrix, camera->fov, (float)target->width / (float)target->height, camera->znear, camera->zfar);
	gen_translation_mat4x4(translation_matrix, camera->position[0], camera->position[1], camera->position[2]);
	gen_rotation_mat4x4(rotation_matrix, camera->rotation[0], camera->rotation[1], camera->rotation[2]);

	multiple_mat4x4(rotation_matrix, rotation_matrix, translation_matrix);
	multiple_mat4x4(view_matrix, view_matrix, rotation_matrix);

	glUseProgram(shader_program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "viewMatrix"), 1, GL_TRUE, (const GLfloat*)view_matrix);

	glBindFramebuffer(GL_FRAMEBUFFER, target->FBO);

	GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, buffers);

	glClearDepth(1.0f);
	glClearColor(0.6, 0.6, 0.6, 1.0);

	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	LRenderNode** node;
	array_rewind(scene->draw_node_list);
	while((node = array_next(scene->draw_node_list))){
		LRenderNode_draw(*node);
	}

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_CLAMP);
	glDisable(GL_CULL_FACE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
