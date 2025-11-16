#ifndef FLOAT_H
#define FLOAT_H

#include <stdint.h>
#include <stdio.h>

//Q24.8 if the intager is 32 bits
#define FIXED_SHIFT 8
#define FIXED_SCALE (1 << FIXED_SHIFT)

typedef int32_t fixed_t;
typedef float float_t;

fixed_t float_to_fixed(float_t n);
float_t fixed_to_float(fixed_t n);
int32_t fixed_to_int(fixed_t n);

fixed_t fixed_add(fixed_t a, fixed_t b);
fixed_t fixed_sub(fixed_t a, fixed_t b);
fixed_t fixed_mul(fixed_t a, fixed_t b);
fixed_t fixed_div(fixed_t a, fixed_t b);
fixed_t fixed_abs(fixed_t n);
fixed_t fixed_min(fixed_t a, fixed_t b);
fixed_t fixed_max(fixed_t a, fixed_t b);

#endif
