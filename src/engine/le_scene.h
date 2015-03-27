#ifndef _LE_SCENE_H_
#define _LE_SCENE_H_

#include "ref.h"
#include "le_node.h"

/**
 * [le_scene_load description]
 * @param  file_name [description]
 * @param  node      [description]
 * @return           [description]
 */
LENode* le_scene_load(const char* file_name, LENode* node);


#endif
