#include "ray.h"
#include "ray_math.h"
#include "ray_sphere.h"

real intersect_sphere(shape* s, ray* r)
{
	//PRINT_VEC3(s->info.position, "pos");
	//PRINT_VEC3(r->origin, "ray pos");
	//PRINT_VEC3(r->direction, "ray dir");

	vec3 oc = vec3_sub(s->info.position, r->origin);
	real l2oc = vec3_sqlength(&oc);

	if(l2oc < s->sph.radius * s->sph.radius)
	{
		real tca = vec3_dot(&oc, &r->direction);
		real l2hc = (s->sph.radius*s->sph.radius - l2oc) / 
			vec3_sqlength(&r->direction) + tca*tca;
		//return true;
		return tca + sqrt(l2hc);
	} 
	else 
	{
		real tca = vec3_dot(&oc, &r->direction);

		if (tca < 0) // points away from the sphere
			return 0.f;

		real l2hc = (s->sph.radius*s->sph.radius - l2oc) / 
			vec3_sqlength(&r->direction) + tca*tca;
		
		if(l2hc > 0)
			return tca - sqrt(l2hc);
		else
			return 0.f;
	}
}

shape* make_sphere(vec3* pos, real radius)
{
	assert(radius > 0.f);

	shape* out = (shape*)malloc(sizeof(shape));
	out->info.next = 0;
	out->info.type = ST_SPHERE;
	out->info.position = *pos;
	//out->info.extents = {radius * 2, radius * 2, radius * 2};
	out->info.intersect = intersect_sphere;
	out->info.get_normal = sphere_get_normal;
	material m = {rand()%255,rand()%255,rand()%255,0,false};
	//material m = {0,255,100,0,false};
	out->info.mat = m;
	out->sph.radius = radius;

	return out;
}

vec3 sphere_get_normal(shape* s, vec3* os_pos)
{
	vec3 out = vec3_mul_sc(*os_pos, -1);
	vec3_normalize(&out);
	return out;
}
