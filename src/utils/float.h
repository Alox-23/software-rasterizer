#ifndef FLOAT_H
#define FLOAT_H

#include <stdint.h>

#define FIXED_SHIFT 16
#define FIXED_SCALE (1 << FIXED_SHIFT)

typedef int32_t fixed_t;
typedef int32_t int_t;
typedef float float_t;

fixed_t float_to_fixed(float_t n);
float_t fixed_to_float(fixed_t n);

#endif
