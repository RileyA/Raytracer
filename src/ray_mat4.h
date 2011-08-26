#ifndef ray_mat4_H
#define ray_mat4_H

#include "ray.h"
#include "ray_math.h"

/* A 4x4 transformation matrix */

/* Extract position */
inline static vec3 mat4_pos(mat4* m)
{
	vec3 out = {m->m[3][0],m->m[3][1],m->m[3][2]};
	return out;
}

/* Extract rotation as a quaternion */
quat mat4_quat(mat4* m);

/* Extract rotation as a 3x3 matrix */
inline static mat3 mat4_mat3(mat4* m)
{
	mat3 out = {
		m->m[0][0],m->m[0][1],m->m[0][2],
		m->m[1][0],m->m[1][1],m->m[1][2],
		m->m[2][0],m->m[2][1],m->m[2][2]};
	return out;
}

/* Invert matrix */
void mat4_invert(mat4* m);

/* Transpose matrix */
mat4 mat4_transpose(mat4* m);

/* Transpose matrix in place */
void mat4_transpose_ip(mat4* m);

#endif
