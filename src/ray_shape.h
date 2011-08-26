#ifndef ray_shape_H
#define ray_shape_H

#include "ray.h"
#include "ray_math.h"
#include "ray_material.h"

union shape;
typedef union shape shape;

enum shape_type
{
	ST_SPHERE,
	ST_PLANE
};

typedef enum shape_type shape_type;

struct sphere
{
	shape* next;
	shape_type type;
	vec3 position;
	vec3 extents;
	real (* intersect)(shape*, ray*);
	vec3 (* get_normal)(shape*, vec3*);
	material mat;

	real radius;
};

typedef struct sphere sphere;

struct plane
{
	shape* next;
	shape_type type;
	vec3 position;
	vec3 extents;
	real (* intersect)(shape*, ray*);
	vec3 (* get_normal)(shape*, vec3*);
	material mat;

	real distance;
	vec3 normal;
};

typedef struct plane plane;

/* Allows some crude polymorphism */
union shape
{
	/* pray the compiler doesn't decide to change the ordering to pack this... */
	struct
	{
		union shape* next;
		shape_type type;
		vec3 position;
		vec3 extents;
		real (* intersect)(shape*, ray*);
		vec3 (* get_normal)(shape*, vec3*);
		material mat;
	} info;

	sphere sph;
	plane pln;
};


void shapes_add(shape* list, shape* next);
int shapes_length(shape* list);
void shapes_free(shape* list);

#endif


