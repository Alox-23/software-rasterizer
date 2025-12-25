#include "vec.h"

void print_vec4f(char* name, vec4f_t a){
  printf("%s = (%f, %f, %f, %f)\n", name, a.x, a.y, a.z, a.w);
}

vec4f_t make_random_vec4f(){
  int rand_x = rand();
  int rand_y = rand();
  int rand_z = rand();
  
  float x = (float)rand_x / RAND_MAX;
  float y = (float)rand_y / RAND_MAX;
  float z = (float)rand_z / RAND_MAX;

  return (vec4f_t){x, y, z, 1.f};
};

//basic arithmetic but pointers hehehe
void padd_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] + b->v[i];
  }
}

void psub_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] - b->v[i];
  }
}

void pmul_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] * b->v[i];
  }
}

void pscl_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, float s){
  for (int i = 0; i < 4; i++){
    r->v[i] = a->v[i] * s;
  }
}

// basic arithmetic
vec4f_t add_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = a.v[i] + b.v[i];
  }
 
  return result;
}

vec4f_t sub_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = a.v[i] - b.v[i];
  }
 
  return result;
}

vec4f_t mul_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = a.v[i] * b.v[i];
  }

  return result;
}

vec4f_t scl_vec4f(vec4f_t a, float s){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = a.v[i] * s;
  }

  return result;
}

// complex functions
vec4f_t neg_vec4f(vec4f_t a){
  return (vec4f_t){-a.x, -a.y, -a.z, 0};
}

float dot_vec4f(vec4f_t a, vec4f_t b){
  float result = 0;

  for (int i = 0; i < 4; i++){
    result = result + a.v[i] * b.v[i]; // result += a[i] * b[i]
  }

  return result;
}

float mag_sq_vec4f(vec4f_t a){
   return a.x*a.x + a.y*a.y + a.z*a.z; // ignoire w component
}

vec4f_t nrm_vec4f(vec4f_t a){
  float len_sq = mag_sq_vec4f(a);

  if (len_sq > 0){
    float inv_len = 1 / sqrt(len_sq);
    return (vec4f_t){
      a.x * inv_len,
      a.y * inv_len,
      a.z * inv_len,
      0 
    };
  }
}

vec4f_t pdiv_vec4f(vec4f_t v){
  v.x /= v.w;
  v.y /= v.w;
  v.z /= v.w;
  return v;
}

float dst_sq_vec4f(vec4f_t a, vec4f_t b){
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  float dz = a.z - b.z;
  return dx*dx + dy*dy + dz*dz;
}

float det2d_vec4f(vec4f_t a, vec4f_t b){
  return a.x * b.y - a.y * b.x;
} 

bool left_or_top_edge(vec4f_t start, vec4f_t end){
  vec4f_t edge = sub_vec4f(end, start);

  const bool is_left_edge = edge.y > 0;
  const bool is_top_edge = edge.y == 0 && edge.x < 0;
  return is_left_edge || is_top_edge;
}
//utility functions
vec4f_t min_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fmin(a.v[i], b.v[i]);
  }

  return result;
}

vec4f_t max_vec4f(vec4f_t a, vec4f_t b){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fmax(a.v[i], b.v[i]);
  }

  return result;
}

vec4f_t flr_vec4f(vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = floor(a.v[i]);
  }
  
  return result;
}

vec4f_t cil_vec4f(vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = ceil(a.v[i]);
  }
  
  return result;
}

vec4f_t abs_vec4f(vec4f_t a){
  vec4f_t result;

  for (int i = 0; i < 4; i++){
    result.v[i] = fabs(a.v[i]);
  }

  return result;
}
