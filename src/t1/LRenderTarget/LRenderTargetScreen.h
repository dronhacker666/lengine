#ifndef _LRENDER_TARGET_SCREEN_H_
#define _LRENDER_TARGET_SCREEN_H_

typedef struct LRenderTargetScreen LRenderTargetScreen;

#include "LRenderTarget.h"

/**
 * LRenderTargetScreen
 */

struct LRenderTargetScreen {


};

LRenderTargetScreen* 	LRenderTargetScreen_create 	(LRenderTarget*);
void 					LRenderTargetScreen_free 	(LRenderTargetScreen*);

#endif
