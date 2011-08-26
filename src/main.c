#include <stdio.h>
#include <time.h>
#include "ray_math.h"
#include "ray_sphere.h"
#include "ray_trace_simple.h"

#include "SDL/SDL.h"

int main(int argc, char** argv)
{
	srand(time(0));
	vec3 v = {0,100,350};
	vec3 v2 = {100,2,350};
	vec3 v3 = {110,2,250};

	shape* list = make_sphere(&v, 100.f);
	shapes_add(list, make_sphere(&v2, 30.f));
	shapes_add(list, make_sphere(&v3, 30.f));

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Surface* surf = SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	trace_simple(list, 640, 480, (uint32_t*)surf->pixels);

	/*int i = 0;

	for(; i < 640*480; ++i)
	{
		uint32_t* px = (uint32_t*)surf->pixels + i;
		*px = SDL_MapRGB(surf->format, 0, 120, 180);
		SDL_UpdateRect(surf, i % 640, i / 640, 1, 1);
	}*/

	SDL_Flip(surf);

	printf("done!\n");


	sleep(3);

	SDL_Quit();

	shapes_free(list);

	return 0;
}
