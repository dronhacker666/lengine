#ifndef _LSCENE_H_
#define _LSCENE_H_

#include <stdlib.h>

typedef struct LScene LScene;
typedef struct LSceneNode LSceneNode;

struct LScene {
	LSceneNode* root;
};

typedef enum {
	LSCENENODETYPE_ROOT,
	LSCENENODETYPE_LIGHT,
} LSceneNodeType;

struct LSceneNode {
	LSceneNodeType type;
	LSceneNode* parent;
	LSceneNode* previous;
	LSceneNode* next;
	LSceneNode* children;
};

#endif
