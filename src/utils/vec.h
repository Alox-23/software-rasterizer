#ifndef VECTOR_H
#define VECTOR_H

#include "float.h"

typedef struct{
  fixed_t x, y, z, w;
} vec4f_t;

vec4f_t init_vec4f(float_t x, float_t y, float_t z);

#endif
