#ifndef VECTOR_H
#define VECTOR_H

#include "float.h"

typedef struct{
  int32_t x, y, z, w;
} vec4i_t;

typedef struct{
  fixed_t x, y, z, w;
} vec4f_t;

vec4i_t init_vec4i(int32_t x, int32_t y, int32_t z);
vec4f_t init_vec4f(float_t x, float_t y, float_t z);

#endif
