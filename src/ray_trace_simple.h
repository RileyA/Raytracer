#ifndef ray_trace_H
#define ray_trace_H

#include "ray.h"
#include "ray_math.h"
#include "ray_shape.h"
#include "ray_color.h"

/* Does a simple raycast (and recurses, does lighting calculations, 
 * etc as needed) and returns a color value. */
color cast_simple(shape* shapes, light* lights, ray r, int depth);

/* Does the raycast only, no other calculations, returns whether or not
 * it hit anything (also passes back hit distance and a pointer to the hit shape) */
bool raycast_simple(shape* shapes, ray r, real dist, shape* hit_shape);

/* very slow, no raycasting optimizations */
void trace_simple(shape* shapes, int w, int h, uint32_t* out);

#endif
