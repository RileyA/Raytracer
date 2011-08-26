#ifndef ray_scene_H
#define ray_scene_H

#include "ray_shape.h"
#include "ray_light.h"

// a scene, with 
struct scene
{
	light* lights;
	shape* shapes;
};

typedef struct scene scene;

#endif
