#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include "vec.h"

typedef uint32_t color_t;

//color
color_t vec4f_to_color(vec4f_t v);
color_t make_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint8_t get_r(color_t c);
uint8_t get_g(color_t c);
uint8_t get_b(color_t c);
uint8_t get_a(color_t c);
void set_r(color_t *c, uint8_t new_value);
void set_g(color_t *c, uint8_t new_value);
void set_b(color_t *c, uint8_t new_value);
void set_a(color_t *c, uint8_t new_value);

#endif
