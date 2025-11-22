#ifndef FLOAT_H
#define FLOAT_H

#include <stdint.h>
#include <stdio.h>

//Q24.8 if the intager is 32 bits
#define FIXED_SHIFT 8
#define FIXED_SCALE (1 << FIXED_SHIFT)
//constants used alot in functions, mainly vector stuf
#define MINUS_ONE_F (-1 * FIXED_SCALE)
#define ONE_F (1 * FIXED_SCALE)

typedef int32_t fixed_t;

fixed_t float_to_fixed(float n);
float fixed_to_float(fixed_t n);
int32_t fixed_to_int(fixed_t n);

fixed_t fixed_add(fixed_t a, fixed_t b);
fixed_t fixed_sub(fixed_t a, fixed_t b);
fixed_t fixed_mul(fixed_t a, fixed_t b);
fixed_t fixed_div(fixed_t a, fixed_t b);
fixed_t fixed_sqrt(fixed_t N);
fixed_t fixed_abs(fixed_t n);
fixed_t fixed_min(fixed_t a, fixed_t b);
fixed_t fixed_max(fixed_t a, fixed_t b);
fixed_t fixed_ex2(fixed_t a);
fixed_t fixed_flr(fixed_t a);
fixed_t fixed_cil(fixed_t a);

#endif
