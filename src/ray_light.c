#include "ray_light.h"

light* make_light_point(vec3 position, color c)
{
	light* lt = malloc(sizeof(light));
	lt->position = position;
	lt->col = c;
	lt->type = LT_POINT;
	lt->next = 0;
	return lt;
}

void lights_add(light* list, light* add)
{
	light* l = list;
	while(l->next && (l = l->next)){}
	l->next = add;
	add->next = 0;
}

void lights_free(light* list)
{
	light* l;
	while((l = list) && ((list = list->next) || l))
		free(l);
}
