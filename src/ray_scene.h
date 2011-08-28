#ifndef ray_scene_H
#define ray_scene_H

#include "ray.h"
#include "ray_shape.h"
#include "ray_light.h"

/* a scene */
struct scene
{
	light* lights;
	shape* shapes;

	bool ambient_occlusion;
	int ambient_occlusion_samples;
};

typedef struct scene scene;

scene* create_simple_scene();

#endif
