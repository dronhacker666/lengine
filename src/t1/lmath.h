#ifndef _L_MATH_H_
#define _L_MATH_H_

#include <math.h>

#define M_PI 3.14159265358979323846

typedef float Vec3[3];
typedef float Mat4x4[4][4];

void gen_identity_mat4x4 	(Mat4x4 res);
void gen_perspective_mat4x4 (Mat4x4 res, float fovy, float aspect, float znear, float zfar);
void gen_translation_mat4x4 (Mat4x4 res, float x, float y, float z);
void gen_rotation_mat4x4 	(Mat4x4 res, float x, float y, float z);
void multiple_mat4x4 		(Mat4x4 res, Mat4x4 m1, Mat4x4 m2);

#endif
