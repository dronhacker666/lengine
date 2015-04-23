#include "lmath.h"

void gen_identity_mat4x4(Mat4x4 m)
{
	Mat4x4 _m = {
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1},
	};
	memcpy(m, &_m, sizeof(Mat4x4));
}

void gen_perspective_mat4x4(Mat4x4 m, float fovy, float aspect, float znear, float zfar)
{

	const float f = 1 / tanf(fovy / 2);
	const float A = (zfar + znear) / (znear - zfar);
	const float B = (2 * zfar * znear) / (znear - zfar);

	Mat4x4 _m = {
		{f/aspect, 0, 0, 0},
		{0,        f, 0, 0},
		{0,        0, A, B},
		{0,        0,-1, 0},
	};
	memcpy(m, &_m, sizeof(Mat4x4));
}

void gen_translation_mat4x4(Mat4x4 m, float x, float y, float z)
{
	gen_identity_mat4x4(m);
	m[0][3] = x;
	m[1][3] = y;
	m[2][3] = z;
}

void gen_rotation_mat4x4(Mat4x4 m, float x, float y, float z)
{
	x = M_PI/180 * x;
	y = M_PI/180 * y;
	z = M_PI/180 * z;
	const float A = cosf(x);
	const float B = sinf(x);
	const float C = cosf(y);
	const float D = sinf(y);
	const float E = cosf(z);
	const float F = sinf(z);
	const float AD = A * D;
	const float BD = B * D;

	Mat4x4 _m = {
		{C*E,       -C*F,      D,    0},
		{BD*E+A*F,  -BD*F+A*E, -B*C, 0},
		{-AD*E+B*F, AD*F+B*E,  A*C,  0},
		{0,         0,         0,    1},
	};
	memcpy(m, &_m, sizeof(Mat4x4));
}

void multiple_mat4x4(Mat4x4 m, Mat4x4 m1, Mat4x4 m2)
{
	Mat4x4 _m = {
		{
			m1[0][0]*m2[0][0] + m1[0][1]*m2[1][0] + m1[0][2]*m2[2][0] + m1[0][3]*m2[3][0],
			m1[0][0]*m2[0][1] + m1[0][1]*m2[1][1] + m1[0][2]*m2[2][1] + m1[0][3]*m2[3][1],
			m1[0][0]*m2[0][2] + m1[0][1]*m2[1][2] + m1[0][2]*m2[2][2] + m1[0][3]*m2[3][2],
			m1[0][0]*m2[0][3] + m1[0][1]*m2[1][3] + m1[0][2]*m2[2][3] + m1[0][3]*m2[3][3],
		},
		{
			m1[1][0]*m2[0][0] + m1[1][1]*m2[1][0] + m1[1][2]*m2[2][0] + m1[1][3]*m2[3][0],
			m1[1][0]*m2[0][1] + m1[1][1]*m2[1][1] + m1[1][2]*m2[2][1] + m1[1][3]*m2[3][1],
			m1[1][0]*m2[0][2] + m1[1][1]*m2[1][2] + m1[1][2]*m2[2][2] + m1[1][3]*m2[3][2],
			m1[1][0]*m2[0][3] + m1[1][1]*m2[1][3] + m1[1][2]*m2[2][3] + m1[1][3]*m2[3][3],
		},
		{
			m1[2][0]*m2[0][0] + m1[2][1]*m2[1][0] + m1[2][2]*m2[2][0] + m1[2][3]*m2[3][0],
			m1[2][0]*m2[0][1] + m1[2][1]*m2[1][1] + m1[2][2]*m2[2][1] + m1[2][3]*m2[3][1],
			m1[2][0]*m2[0][2] + m1[2][1]*m2[1][2] + m1[2][2]*m2[2][2] + m1[2][3]*m2[3][2],
			m1[2][0]*m2[0][3] + m1[2][1]*m2[1][3] + m1[2][2]*m2[2][3] + m1[2][3]*m2[3][3],
		},
		{
			m1[3][0]*m2[0][0] + m1[3][1]*m2[1][0] + m1[3][2]*m2[2][0] + m1[3][3]*m2[3][0],
			m1[3][0]*m2[0][1] + m1[3][1]*m2[1][1] + m1[3][2]*m2[2][1] + m1[3][3]*m2[3][1],
			m1[3][0]*m2[0][2] + m1[3][1]*m2[1][2] + m1[3][2]*m2[2][2] + m1[3][3]*m2[3][2],
			m1[3][0]*m2[0][3] + m1[3][1]*m2[1][3] + m1[3][2]*m2[2][3] + m1[3][3]*m2[3][3],
		},
	};
	memcpy(m, &_m, sizeof(Mat4x4));
}

