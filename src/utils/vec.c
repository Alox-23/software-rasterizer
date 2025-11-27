#include "vec.h"

void print_vec4f(char* name, vec4f_t a){
  printf("%s = (%f, %f, %f, %f)\n", name, fixed_to_float(a.x), fixed_to_float(a.y), fixed_to_float(a.z), fixed_to_float(a.w));
}

//color
color_t vec4f_to_color(vec4f_t v){
  float r_int = fixed_to_float(v.x);
  float g_int = fixed_to_float(v.y);
  float b_int = fixed_to_float(v.z);
  float a_int = fixed_to_float(v.w);

  uint8_t r = (uint8_t)imax(0, imin(255, r_int));
  uint8_t g = (uint8_t)imax(0, imin(255, g_int));
  uint8_t b = (uint8_t)imax(0, imin(255, b_int));
  uint8_t a = (uint8_t)imax(0, imin(255, a_int));

  printf("RGBA = %d\n", imin(255, ));
  
  return make_color(r, g, b, a);
}

color_t make_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
  return (color_t)r |
         ((color_t)g << 8) |
         ((color_t)g << 16) |
         ((color_t)g << 24);
}

uint8_t get_r(color_t c){
  return (uint8_t)(c & 0xFF);
}

uint8_t get_g(color_t c){
  return (uint8_t)((c >> 8) & 0xFF);
}

uint8_t get_b(color_t c){
  return (uint8_t)((c >> 16) & 0xFF);
}

uint8_t get_a(color_t c){
  return (uint8_t)((c >> 24) & 0xFF);
}

void set_r(color_t *c, uint8_t new_val){
  *c = (*c & ~0xFF) | new_val;
}

void set_g(color_t *c, uint8_t new_val){
  *c = (*c & ~(0xFF << 8)) | ((color_t)new_val << 8);
}

void set_b(color_t *c, uint8_t new_val){
  *c = (*c & ~(0xFF << 16)) | ((color_t)new_val << 16);
}

void set_a(color_t *c, uint8_t new_val){
  *c = (*c & ~(0xFF << 24)) | ((color_t)new_val << 24);
}

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
  fixed_t result = 0;

  for (int i = 0; i < 4; i++){
    result = fixed_add(result, fixed_mul(a.v[i], b.v[i])); // result += a[i] * b[i]
  }

  return result;
}

fixed_t mag_sq_vec4f(vec4f_t a){
   return fixed_ex2(a.x) + fixed_ex2(a.y) + fixed_ex2(a.z); // ignoire w component
}

vec4f_t nrm_vec4f(vec4f_t a){
  fixed_t len_sq = fixed_add(fixed_ex2(a.x), fixed_add(fixed_ex2(a.y), fixed_ex2(a.z)));

  if (len_sq > 0){
    fixed_t inv_len = fixed_div(ONE_F, fixed_sqrt(len_sq));
    return (vec4f_t){
      fixed_mul(a.x, inv_len),
      fixed_mul(a.y, inv_len),
      fixed_mul(a.z, inv_len),
      0 
    };
  }
}

fixed_t dst_sq_vec4f(vec4f_t a, vec4f_t b){
  fixed_t dx = fixed_sub(a.x, b.x);
  fixed_t dy = fixed_sub(a.y, b.y);
  fixed_t dz = fixed_sub(a.z, b.z);
  return fixed_ex2(dx) + fixed_ex2(dy) + fixed_ex2(dz);
}

fixed_t det2d_vec4f(vec4f_t a, vec4f_t b){
  return fixed_sub(fixed_mul(a.x, b.y), fixed_mul(a.y, b.x));
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
