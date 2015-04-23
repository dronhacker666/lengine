#include "LRenderTargetScreen.h"

LRenderTargetScreen* LRenderTargetScreen_create(LRenderTarget* target)
{
	LRenderTargetScreen* screen = calloc(1, sizeof(LRenderTargetScreen));

	return screen;
}

void LRenderTargetScreen_free(LRenderTargetScreen* screen)
{
	free(screen);
}
