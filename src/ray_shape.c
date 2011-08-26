#include "ray.h"
#include "ray_math.h"
#include "ray_shape.h"

int shapes_length(shape* list)
{
	int count = 0;

	shape* s = list;
	for(; s; s = s->info.next)
		++count;

	return count;
}

void shapes_add(shape* list, shape* next)
{
	shape* s = list;
	while(s->info.next && (s = s->info.next)){}
	s->info.next = next;
	next->info.next = 0;
}

void shapes_free(shape* list)
{
	shape* s;
	while((s = list) && ((list = list->info.next) || s))
		free(s);
}
