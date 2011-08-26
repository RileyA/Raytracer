#ifndef ray_vec3_H
#define ray_vec3_H

#include "ray.h"
#include "ray_math.h"

#define PRINT_VEC3(V, S) printf("Vec3 %s: %f %f %f\n", S, V.x, V.y, V.z)

/* Some constants */
static const vec3 vec3_ZERO = {0,0,0};
static const vec3 vec3_UNIT_X = {1,0,0};
static const vec3 vec3_UNIT_Y = {0,1,0};
static const vec3 vec3_UNIT_Z = {0,0,1};
static const vec3 vec3_NEGATIVE_UNIT_X = {-1,0,0};
static const vec3 vec3_NEGATIVE_UNIT_Y = {0,-1,0};
static const vec3 vec3_NEGATIVE_UNIT_Z = {0,0,-1};

/* A whole bunch of inlined vector operations: */

/* dot product */
static inline real vec3_dot(vec3* v1, vec3* v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/* length */
static inline real vec3_length(vec3* v)
{
	return sqrt(
		v->x * v->x +
		v->y * v->y +
		v->z * v->z);
}

/* squared length */
static inline real vec3_sqlength(vec3* v)
{
	return
		v->x * v->x +
		v->y * v->y +
		v->z * v->z;
}

/* cross product */
static inline vec3 vec3_cross(vec3* v1, vec3* v2)
{
	vec3 out = {
		v1->x * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z,
		v1->x * v2->y - v1->y * v2->x};
	return out;
}

/* addition */
static inline vec3 vec3_add(vec3 v1, vec3 v2)
{
	vec3 out = {
		v1.x + v2.x, 
		v1.y + v2.y, 
		v1.z + v2.z};
	return out;
}

/* in place addition */
static inline void vec3_add_ip(vec3* v1, vec3 v2)
{
	v1->x += v2.x;
	v1->y += v2.y;
	v1->z += v2.z;
}

/* subtraction */
static inline vec3 vec3_sub(vec3 v1, vec3 v2)
{
	vec3 out = {
		v1.x - v2.x, 
		v1.y - v2.y, 
		v1.z - v2.z};
	return out;
}

/* in place subtraction */
static inline void vec3_sub_ip(vec3* v1, vec3 v2)
{
	v1->x -= v2.x;
	v1->y -= v2.y;
	v1->z -= v2.z;
}

/* multiplication by scalar (multiplies each component) */
static inline vec3 vec3_mul_sc(vec3 v1, real scalar)
{
	vec3 out = {
		v1.x * scalar,
		v1.y * scalar, 
		v1.z * scalar};
	return out;
}

/* multiplication (multiplies each component) */
static inline vec3 vec3_mul(vec3* v1, vec3* v2)
{
	vec3 out = {
		v1->x * v2->x,
		v1->y * v2->y, 
		v1->z * v2->z};
	return out;
}

/* in-place multiplication (multiplies each component) */
static inline void vec3_mul_ip(vec3* v1, vec3* v2)
{
	v1->x *= v2->x;
	v1->y *= v2->y;
	v1->z *= v2->z;
}

static inline real vec3_normalize(vec3* v)
{
	real length = sqrt(v->x*v->x + v->y*v->y + v->z*v->z);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	return length;
}

#endif
