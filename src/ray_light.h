#ifndef ray_light_H
#define ray_light_H

#include "ray.h"
#include "ray_math.h"
#include "ray_color.h"

enum light_type
{
	LT_POINT,
	LT_SPOT,
	LT_DIRECTIONAL
};

typedef enum light_type light_type;

struct light
{
	// type
	light_type type;

	// location info
	vec3 position;
	vec3 direction;

	// material info
	color col;
	bool diffuse;
	bool specular;
	bool shadows;
	// todo: shadow properties...
	
	// for spotlight
	real radius_inner;
	real radius_outer;

	// for linked listage
	struct light* next;

	// attenuation
	struct
	{
		real constant;
		real linear;
		real quadratic;
		real range;
	} attenuation;

};

typedef struct light light;

light* make_light_point(vec3 position, color c);
light* make_light_spot(vec3 position);
light* make_light_directional(vec3 position);
light* make_pointlight(vec3 position);

void lights_add(light* list, light* add);
void lights_free(light* list);

#endif

