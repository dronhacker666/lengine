#include "lscene.h"

int main(void)
{
	LScene* scene = LScene_create();

	LSceneNode* box1 = LSceneNode_create();
	LSceneNode* box2 = LSceneNode_create();

	LSceneNode_append(scene->root, box1);
	LSceneNode_append(scene->root, box2);

	return 0;
}
