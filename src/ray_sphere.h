#ifndef ray_sphere_H
#define ray_sphere_H

#include "ray.h"
#include "ray_math.h"
#include "ray_shape.h"

real intersect_sphere(shape* s, ray* r);
shape* make_sphere(vec3* pos, real radius);
vec3 sphere_get_normal(shape* s, vec3* os_pos);

#endif

