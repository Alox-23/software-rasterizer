#ifndef MAT_H
#define MAT_H

#include "float.h"

typedef struct{
  int32_t m[4][4]; 
} mat4i_t;

typedef struct{
  fixed_t m[4][4];
} mat4f_t;

mat4i_t init_mat4i(int32_t x, int32_t y, int32_t z);
mat4f_t init_mat4f(float_t x, float_t y, float_t z);

#endif
