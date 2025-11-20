#ifndef VECTOR_H
#define VECTOR_H

#include "float.h"

//x and v[0] share the same memory location 
//so they are the same variable that can be assesed by different identifiers
typedef union{
  fixed_t x, y, z, w;
  fixed_t v[4];
} vec4f_t;

vec4f_t add_vec4f(vec4f_t a, vec4f_t a);
vec4f_t sub_vec4f(vec4f_t a, vec4f_t a);
vec4f_t mul_vec4f(vec4f_t a, vec4f_t a);
vec4f_t scl_vec4f(vec4f_t a, fixed_t a);

#endif
