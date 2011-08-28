#include "ray_trace_simple.h"

color cast_simple(scene* sce, ray* r, int depth)
{
	color out = {0,0,0,0};
	shape* hit = 0;
	real dist = raycast_simple(sce->shapes, r, &hit);

	if(hit)
	{
		// point we hit (world space)
		vec3 hit_pt = vec3_add(r->origin, vec3_mul_sc(r->direction, dist));

		// object space position
		vec3 os_pos = vec3_sub(hit_pt, hit->info.position);

		// get normal
		vec3 normal = hit->info.get_normal(hit, &os_pos);

		color lit = {0,0,0,0};

		light* l = sce->lights;

		if(l)
		{
			do
			{
				color lt_c = l->col;

				// get object space light dir
				vec3 os_light_dir = vec3_sub(hit->info.position, l->position);
				vec3_normalize(&os_light_dir);

				// fragment space light direction
				vec3 fs_light_dir = vec3_sub(hit_pt, l->position);
				vec3_normalize(&fs_light_dir);

				real shadow_factor = 1.f;
				ray shadowray = {l->position,fs_light_dir};
				shape* shadow_hit = 0;

				raycast_simple(sce->shapes, &shadowray, &shadow_hit);

				if(shadow_hit != hit && shadow_hit)
					shadow_factor -= 0.8f;

				// diffuse shading (plain ol' lambert)
				real lambert = vec3_dot(&os_light_dir, &normal);
				lambert = max(lambert, 0.f);
				color_mult_sc_ip(&lt_c, lambert * shadow_factor);
	 
				color_add_ip_clamp(&lit, lt_c);

			} while(l = l->next);
		}

		color_mult_ip(&lit, hit->info.mat.col);
		color_add_ip(&out, lit);
	}

	return out;
}

real raycast_simple(shape* shapes, ray* r, shape** hit_shape)
{
	shape* s = 0;
	shape* hit = 0;
	real least = 5000000000.f;// lots...
	while((s = shapes) && ((shapes = shapes->info.next) || s))
	{
		real n = s->info.intersect(s, r);
		if(n!= 0.f && n < least)
		{
			least = n;
			hit = s;
		}
	}

	*hit_shape = hit;

	return hit_shape ? least : 0.f;
}

void trace_simple(scene* sce, int w, int h, uint32_t* out)
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
			
			color c = cast_simple(sce, &r, 0);

			out[j * w + i] = color_to_int(&c);
		}
	}
}
