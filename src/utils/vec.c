#include "vec.h"

vec4f_t add_vec4f(vec4f_t a, vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_add(a.v[i], b.v[i]);
  }
 
  return result;
}

vec4f_t sub_vec4f(vec4f_t a, vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_sub(a.v[i], b.v[i]);
  }
 
  return result;
}

vec4f_t mul_vec4f(vec4f_t a, vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_mul(a.v[i], b.v[i]);
  }

  return result;
}

vec4f_t scl_vec4f(vec4f_t a, fixed_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_mul(a.v[i], a);
  }

  return result;
}
