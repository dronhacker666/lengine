#include "LRenderTarget.h"

LRenderTarget* LRenderTarget_create(LRenderTargetType type, unsigned width, unsigned height)
{
	LRenderTarget* target = calloc(1, sizeof(LRenderTarget));
	target->type = type;
	target->width = width;
	target->height = height;

	switch(target->type){
		case LRENDER_TARGET_SCREEN:
			target->screen = LRenderTargetScreen_create(target);
		break;
		case LRENDER_TARGET_TEXTURE:
			//target->texture = LRenderTargetTexture_create(target);
		break;
	}

	return target;
}

void LRenderTarget_free(LRenderTarget* target)
{
	switch(target->type){
		case LRENDER_TARGET_SCREEN: LRenderTargetScreen_free(target->screen); break;
		//case LRENDER_TARGET_TEXTURE: LRenderTargetTexture_free(target->texture); break;
	}
	free(target);
}
