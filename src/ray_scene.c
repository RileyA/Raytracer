#include "ray.h"
#include "ray_scene.h"

scene* create_simple_scene(shape* shapes, light* lights)
{
	scene* out = malloc(sizeof(scene));
	out->shapes = shapes;
	out->lights = lights;
	return out;
}
