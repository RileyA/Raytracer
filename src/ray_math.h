#ifndef ray_math_H
#define ray_math_H

#include "ray.h"

struct vec3
{
	real x;
	real y;
	real z;
};
typedef struct vec3 vec3;

struct quat
{
	real x;
	real y;
	real z;
	real w;
};
typedef struct quat quat;

struct mat3
{
	real m[4][4];
};
typedef struct mat3 mat3;

struct mat4
{
	real m[4][4];
};
typedef struct mat4 mat4;

struct ray
{
	vec3 origin;
	vec3 direction;
};
typedef struct ray ray;

#include "ray_vec3.h"
#include "ray_mat4.h"
#include "ray_mat3.h"
#include "ray_quat.h"
#include "ray_ray.h"

#endif
