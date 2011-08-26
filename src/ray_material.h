#ifndef ray_material_H
#define ray_material_H

#include "ray.h"
#include "ray_math.h"
#include "ray_color.h"

struct material
{
	color col;
	bool reflective;
};

typedef struct material material;

#endif
