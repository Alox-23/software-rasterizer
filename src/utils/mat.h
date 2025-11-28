#ifndef MAT_H
#define MAT_H

#include "vec.h"

typedef struct{
  float m[4][4];
} mat4f_t;

mat4f_t mul_mat4f(mat4f_t a, mat4f_t b);
vec4f_t mul_matvec4f(mat4f_t m, vec4f_t v);

#endif
