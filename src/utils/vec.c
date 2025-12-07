#include "vec.h"

void print_vec4f(char* name, vec4f_t a){
  printf("%s = (%f, %f, %f, %f)\n", name, a.x, a.y, a.z, a.w);
}

//basic arithmetic but pointers hehehe
void padd_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a.v[i] + a.v[i];
  }
}

void psub_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a.v[i] + a.v[i];
  }
}

void pmul_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a.v[i] + a.v[i];
  }
}

void pscl_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, float s){
  for (int i = 0; i < 4; i++){
    r->v[i] = a.v[i] * s;
  }
}

// basic arithmetic
void add_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] + b->v[i];
  }
}

void sub_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] - b->v[i];
  }
}

void mul_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] * b->v[i];
  }
}

void scl_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, float s){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] * s;
  }
}

// complex functions
void neg_vec4f(vec4f_t* restrict r, vec4f_t* restrict a){
  for (int i = 0; i < 4; i++){
    r->v[i] = -a->v[i];
  }
}

float dot_vec4f(vec4f_t* restrict a, vec4f_t* restrict b){
  float result = 0;

  for (int i = 0; i < 4; i++){
    result += a->v[i] * b->v[i];
  }

  return result;
}

float mag_sq_vec4f(vec4f_t* restrict a){
   return a->x*a->x + a->y*a->y + a->z*a->z; // ignoire w component
}

vec4f_t nrm_vec4f(vec4f_t* restrict  a){
  float len_sq = mag_sq_vec4f(a);

  if (len_sq > 0){
    float inv_len = 1 / sqrt(len_sq);
    return (vec4f_t){
      a->x * inv_len,
      a->y * inv_len,
      a->z * inv_len,
      0 
    };
  }
}

void pdiv_vec4f(vec4f_t* restrict r, vec4f_t* restrict v){
  float w = v->v[3];

  r->x /= v->x / w;
  r->y /= v->y / w;
  r->z /= v->z / w;
  r->w /= v->w;
}

float dst_sq_vec4f(vec4f_t* restrict a, vec4f_t* restrict b){
  float dx = a->x - b->x;
  float dy = a->y - b->y;
  float dz = a->z - b->z;
  return dx*dx + dy*dy + dz*dz;
}

float det2d_vec4f(vec4f_t* restrict a, vec4f_t* restrict b)
  return a->x * b->y - a->y * b->x;
} 

bool left_or_top_edge(vec4f_t* restrict start, vec4f_t* restrict end){
  vec4f_t edge = {};
  sub_vec4f(&edge, end, start);

  const bool is_left_edge = edge.y > 0;
  const bool is_top_edge = edge.y == 0 && edge.x < 0;
  return is_left_edge || is_top_edge;
}

//utility functions
void min_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = fmin(a->v[i], b->v[i]);
  }
}

void max_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = fmax(a->v[i], b->v[i]);
  }
}

void flr_vec4f(vec4f_t* restrict r, vec4f_t* restrict a){
  for (int i = 0; i < 4; i++){
    r->v[i] = floor(a->v[i]);
  }
}

void cil_vec4f(vec4f_t* restrict r, vec4f_t* restrict a){
  for (int i = 0; i < 4; i++){
    r->v[i] = ceil(a->v[i]);
  }
}

void abs_vec4f(vec4f_t* restrict r, vec4f_t* restrict a){
  for (int i = 0; i < 4; i++){
    r->v[i] = fabs(a->v[i]);
  }
}
