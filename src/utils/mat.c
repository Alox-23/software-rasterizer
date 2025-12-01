#include "mat.h"

void print_mat4f(char* name, mat4f_t m){
  printf("%s={\n\t{%.3f, %.3f, %.3f, %.3f}\n\t{%.3f, %.3f, %.3f, %.3f}\n\t{%.3f, %.3f, %.3f, %.3f}\n\t{%.3f, %.3f, %.3f, %.3f}\n}",
         name,
         m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
         m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
         m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
         m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]
         );
}

mat4f_t make_identity_mat4f(){
  mat4f_t result = {
    {
      {1.f, 0.f, 0.f, 0.f},
      {0.f, 1.f, 0.f, 0.f},
      {0.f, 0.f, 1.f, 0.f},
      {0.f, 0.f, 0.f, 1.f},
    },
  };

  return result;
}

mat4f_t make_translation_mat4f(vec4f_t v){
  mat4f_t result = {
    {
      {1.f, 0.f, 0.f, v.x},
      {0.f, 1.f, 0.f, v.y},
      {0.f, 0.f, 1.f, v.z},
      {0.f, 0.f, 0.f, 1.f},
    },
  };

  return result;
}

mat4f_t make_scale_mat4f(vec4f_t s){
  mat4f_t result = {
    {
      {s.x, 0.f, 0.f, 0.f},
      {0.f, s.y, 0.f, 0.f},
      {0.f, 0.f, s.z, 0.f},
      {0.f, 0.f, 0.f, 1.f},
    },
  };

  return result;
}

mat4f_t make_rotationXY_mat4f(float angle){
  
  float cosa = cos(angle);
  float sina = sin(angle);

  mat4f_t result = {
    {
      {cosa, -sina, 0.f, 0.f},
      {sina,  cosa, 0.f, 0.f},
      {0.f, 0.f, 1.f, 0.f},
      {0.f, 0.f, 0.f, 1.f},
    },
  };

  return result;
}

mat4f_t make_rotationYZ_mat4f(float angle){
  
  float cosa = cos(angle);
  float sina = sin(angle);

  mat4f_t result = {
    {
      {1.f, 0.f,  0.f, 0.f},
      {0.f, cosa, -sina, 0.f},
      {0.f, sina,  cosa, 0.f},
      {0.f, 0.f,  0.f, 1.f},
    },
  };

  return result;
}

mat4f_t make_rotationZX_mat4f(float angle){
  
  float cosa = cos(angle);
  float sina = sin(angle);

  mat4f_t result = {
    {
      { cosa, 0.f, sina, 0.f},
      { 0.f, 1.f, 0.f, 0.f},
      {-sina, 0.f, cosa, 0.f},
      { 0.f, 0.f, 0.f, 1.f},
    },
  };

  return result;
}

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
  vec4f_t result = {0.f, 0.f, 0.f, 0.f};

  for (int i = 0; i < 4; i++){
    float sum = 0.0f;

    for (int j = 0; j < 4; j++){
      sum += m.m[i][j] * v.v[j];
    }

    result.v[i] = sum;
  }

  return result;
}
