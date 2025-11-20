#include "mat.h"

mat4f_t mul_mat4f(mat4f_t a, mat4f_t b){
  Mat4 result = {0};
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result.m[i][j] += a.m[i][k] * b.m[k][j];
      }
    }
  }
  
  return result;
}
