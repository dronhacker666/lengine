#include "LRenderTarget.h"

LRenderTarget* LRenderTarget_create(unsigned width, unsigned height)
{
	LRenderTarget* target = calloc(1, sizeof(LRenderTarget));
	target->width = width;
	target->height = height;

	glGenTextures(1, &target->depth);
	glBindTexture(GL_TEXTURE_2D, target->depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, target->width, target->height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &target->color0);
	glBindTexture(GL_TEXTURE_2D, target->color0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, target->width, target->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &target->color1);
	glBindTexture(GL_TEXTURE_2D, target->color1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, target->width, target->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &target->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, target->FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target->color0, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, target->color1, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, target->depth, 0);

	//glDrawBuffer(GL_NONE);  glReadBuffer(GL_NONE); // disable color render

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(status!=GL_FRAMEBUFFER_COMPLETE){
		const char* status_text;
		switch(status){
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: status_text = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: status_text = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: status_text = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"; break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: status_text = "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"; break;
			case GL_FRAMEBUFFER_UNSUPPORTED: status_text = "GL_FRAMEBUFFER_UNSUPPORTED"; break;
			default: status_text = "UNKNOWN"; break;
		}
		printf("FrameBuffer status: %s\n", status_text);
		exit(0);
	}

	

	return target;
}

void LRenderTarget_free(LRenderTarget* target)
{
	glDeleteFramebuffers(1, &target->FBO);
	glDeleteTextures(1, &target->depth);
	glDeleteTextures(1, &target->color0);
	glDeleteTextures(1, &target->color1);
	free(target);
}
