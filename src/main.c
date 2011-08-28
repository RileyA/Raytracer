#include <stdio.h>
#include <time.h>
#include "ray_math.h"
#include "ray_sphere.h"
#include "ray_trace_simple.h"
#include "ray_scene.h"

#include "SDL/SDL.h"

int main(int argc, char** argv)
{
	srand(time(0));
	vec3 v = {0,0,500};
	vec3 v2 = {0,-60,350};
	vec3 v3 = {60,0,390};

	shape* list = make_sphere(&v, 100.f);
	shapes_add(list, make_sphere(&v2, 30.f));
	shapes_add(list, make_sphere(&v3, 40.f));

	vec3 v4 = {250,0,-250};
	color c1 = {255,255,255};
	light* lts = make_light_point(v4, c1);

	scene* sc = create_simple_scene(list, lts);

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* surf = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	trace_simple(sc, 640, 480, (uint32_t*)surf->pixels);

	SDL_Flip(surf);

	printf("done!\n");

	sleep(3);

	SDL_Quit();

	shapes_free(list);
	lights_free(lts);
	free(sc);

	return 0;
}
