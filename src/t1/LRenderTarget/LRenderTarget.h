#ifndef _LRENDER_TARGET_H_
#define _LRENDER_TARGET_H_

typedef struct LRenderTarget LRenderTarget;

typedef enum {
	LRENDER_TARGET_SCREEN,
	LRENDER_TARGET_TEXTURE,
} LRenderTargetType;

#include "../lrender.h"
#include "LRenderTargetScreen.h"

/**
 * LRenderTarget
 */

struct LRenderTarget {
	LRenderTargetType type;
	unsigned width;
	unsigned height;
	union {
		LRenderTargetScreen* screen;
	};
};

LRenderTarget*	LRenderTarget_create 	(LRenderTargetType, unsigned, unsigned);
void 			LRenderTarget_free 		(LRenderTarget*);


#endif
