#include "mat.h"

mat4f_t mul_mat4f(mat4f_t a, mat4f_t b){
  mat4f_t result = {};
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result.m[i][j] += a.m[i][k] * b.m[k][j];
      }
    }
  }
  
  return result;
}

vec4f_t mul_matvec4f(mat4f_t m, vec4f_t v){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    float sum = 0.0f;

    for (int j = 0; j < 4; j++){
      sum += m.m[i][j] * v.v[i];
    }

    result.v[i] = sum;
  }

  return result;
}
