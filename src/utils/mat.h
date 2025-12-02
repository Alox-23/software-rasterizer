#ifndef MAT_H
#define MAT_H

#include "vec.h"

typedef struct{
  float m[4][4];
} mat4f_t;

//utility
void print_mat4f(char* name, mat4f_t m);

//make matrixes
mat4f_t make_identity_mat4f();
mat4f_t make_translation_mat4f(vec4f_t v);
mat4f_t make_scale_mat4f(vec4f_t s);
mat4f_t make_rotationXY_mat4f(float angle);
mat4f_t make_rotationYZ_mat4f(float angle);
mat4f_t make_rotationZX_mat4f(float angle);
mat4f_t make_perspective_mat4f(float near, float far, float fovY, float aspect_ratio);

//combining transformations and applying them
mat4f_t mul_mat4f(mat4f_t a, mat4f_t b);
vec4f_t mul_matvec4f(mat4f_t m, vec4f_t v);

#endif
