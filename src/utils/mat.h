#ifndef MAT_H
#define MAT_H

#include "float.h"

typedef struct{
  fixed_t m[4][4];
} mat4f_t;

mat4f_t init_mat4f(float_t x, float_t y, float_t z);

#endif
