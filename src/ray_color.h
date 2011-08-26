#ifndef ray_color_H
#define ray_color_H

#include "ray.h"
#include "ray_math.h"

struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

typedef struct color color;

union color_convert
{
	color rgba;
	uint32_t c;
};

typedef union color_convert color_convert;

static inline uint32_t color_to_int(color* c)
{
	return c->r<<16 | c->g<<8 | c->b | c->a<<24;
}

static inline void color_add_ip(color* c1, color c2)
{
	c1->r += c2.r;
	c1->g += c2.g;
	c1->b += c2.b;
	c1->a += c2.a;
}

static inline color color_add(color c1, color c2)
{
	color out = {
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a};
	return out;
}

static inline color color_mult_sc(color c1, real scalar)
{
	color out = {
		c1.r * scalar,
		c1.g * scalar,
		c1.b * scalar,
		c1.a * scalar};
	return out;
}

#endif
