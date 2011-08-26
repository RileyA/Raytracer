#include "ray_trace_simple.h"

color cast_simple(shape* shapes, light* lights, ray* r, int depth)//, color* hit)// vec3* normal
{
	color out = {0,0,0,0};
	shape* s;
	real least = 500000.f;
	shape* hit = 0;
	while((s = shapes) && ((shapes = shapes->info.next) || s))
	{
		real n = s->info.intersect(s, r);
		if(n!= 0.f && n < least)
		{
			least = n;
			hit = s;
		}
	}

	if(hit)
	{
		// point we hit (world space)
		vec3 hit_pt = vec3_add(r->origin, vec3_mul_sc(r->direction, least));

		// object space position
		vec3 os_pos = vec3_sub(hit_pt, hit->info.position);

		// get normal
		vec3 normal = hit->info.get_normal(hit, &os_pos);

		vec3 light = {0,1,0};
	
		// compute lighting
		real lambert = vec3_dot(&normal, &light);

		color_add_ip(&out, color_mult_sc(hit->info.mat.col, lambert > 0 ? lambert : 0));
	}

	return out;
}

void trace_simple(shape* shapes, light* lights, int w, int h, uint32_t* out)
{
	int i = 0;

	for(; i < w; ++i)
	{
		int j = 0;

		for(; j < h; ++j)
		{
			vec3 dir = {i-w/2, -(j-h/2), 650};
			vec3_normalize(&dir);
			ray r = {0,0,0, dir};
			
			color c = cast_simple(shapes, &r, 0);

			out[j * w + i] = color_to_int(&c);
		}
	}
}
