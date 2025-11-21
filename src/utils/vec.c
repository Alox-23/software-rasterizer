#include "vec.h"

// basic arithmetic
vec4f_t add_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_add(a.v[i], b.v[i]);
  }
 
  return result;
}

vec4f_t sub_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_sub(a.v[i], b.v[i]);
  }
 
  return result;
}

vec4f_t mul_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_mul(a.v[i], b.v[i]);
  }

  return result;
}

vec4f_t scl_vec4f(vec4f_t a, fixed_t s){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_mul(a.v[i], s);
  }

  return result;
}

// complex functions
vec4f_t neg_vec4f(vec4f_t a){
  return (vec4f_t){-a.x, -a.y, -a.z, 0};
}

fixed_t dot_vec4f(vec4f_t a, vec4f_t b){
  fixed_t result;

  for (int i = 0; i < 4; i++){
    result = fixed_add(result, fixed_mul(a.v[i], b.v[i])); // result += a[i] * b[i]
  }

  return result;
}

fixed_t lg2_vec4f(vec4f_t a){
   return fixed_ex2(a.x) + fixed_ex2(a.y) + fixed_ex2(a.z); // ignoire w component
}

//FIX THIS BULLSHIT
vec4f_t nrm_vec4f(vec4f_t a){
  fixed_t len_sq = fixed_add(fixed_ex2(a.x), fixed_add(fixed_ex2(a.y), fixed_ex2(a.z)));

  if (len_sq > 0){
    fixed_t inv_len = fixed_div(ONE_F, len_sq);
    return (vec4f_t){
      fixed_mul(a.x, inv_len),
      fixed_mul(a.y, inv_len),
      fixed_mul(a.z, inv_len),
      0 
    };
  }
}

fixed_t dt2_vec4f(vec4f_t a, vec4f_t b){
  fixed_t dx = fixed_sub(a.x, b.x);
  fixed_t dy = fixed_sub(a.y, b.y);
  fixed_t dz = fixed_sub(a.z, b.z);
  return fixed_ex2(dx) + fixed_ex2(dy) + fixed_ex2(dz);
}

//utility functions
vec4f_t min_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_min(a.v[i], b.v[i]);
  }

  return result;
}

vec4f_t max_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_max(a.v[i], b.v[i]);
  }

  return result;
}

vec4f_t flr_vec4f(vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_flr(a.v[i]);
  }
  
  return result;
}

vec4f_t cil_vec4f(vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_cil(a.v[i]);
  }
  
  return result;
}

vec4f_t abs_vec4f(vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fixed_abs(a.v[i]);
  }

  return result;
}
