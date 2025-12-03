#include "vec.h"

void print_vec4f(char* name, vec4f_t a){
  printf("%s = (%f, %f, %f, %f)\n", name, a.x, a.y, a.z, a.w);
}

vertex clip_intersect_edge(vertex const v0, vertex const v1, float value0, float value1){
  float t = value0 / (value0 - value1);

  vertex v;
  v.position = add_vec4f(scl_vec4f(v0.position, (1.f -1)), scl_vec4f(v1.position, t));
  v.color = add_vec4f(scl_vec4f(v0.color, (1.f -1)), scl_vec4f(v1.color, t));

  return v;
}

vertex* clip_triangle_single_plane(vertex* triangle, vec4f_t equation, vertex* result){
  float values[3] = {
    dot_vec4f(triangle[0].position, equation),
    dot_vec4f(triangle[1].position, equation),
    dot_vec4f(triangle[2].position, equation),
  };

  uint8_t mask = (values[0] < 0.f ? 1 : 0) | (values[1] < 0.f ? 2 : 0) | (values[2] < 0.f ? 4 : 0);

  switch (mask){
    case 0b000:
      *result++ = triangle[0];
      *result++ = triangle[1];
      *result++ = triangle[2];
      break;
    case 0b001:
      vertex v01 = clip_intersect_edge(triangle[0], triangle[1], values[0], values[1]);
      vertex v02 = clip_intersect_edge(triangle[0], triangle[2], values[0], values[2]);
      *result++ = v01;
      *result++ = triangle[1];
      *result++ = triangle[2];
      *result++ = v01;
      *result++ = triangle[2];
      *result++ = v02;
      break;
    case 0b010:
      vertex v10 = clip_intersect_edge(triangle[1], triangle[0], values[1], values[0]);
      vertex v12 = clip_intersect_edge(triangle[1], triangle[2], values[1], values[2]);
      *result++ = triangle[0];
      *result++ = v10;
      *result++ = triangle[2];
      *result++ = triangle[2];
      *result++ = v10;
      *result++ = v12;
      break;
    case 0b011:
      *result++ = clip_intersect_edge(triangle[0], triangle[2], values[0], values[2]);
      *result++ = clip_intersect_edge(triangle[1], triangle[2], values[1], values[2]);
      *result++ = triangle[2];
      break;
    case 0b100:
      vertex v20 = clip_intersect_edge(triangle[2], triangle[0], values[2], values[0]);
      vertex v21 = clip_intersect_edge(triangle[2], triangle[1], values[2], values[1]);
      *result++ = triangle[0];
      *result++ = triangle[1];
      *result++ = v20;
      *result++ = v20;
      *result++ = triangle[1];
      *result++ = v21;
      break;
    case 0b101:
      *result++ = clip_intersect_edge(triangle[0], triangle[1], values[0], values[1]);
      *result++ = triangle[1];
      *result++ = clip_intersect_edge(triangle[2], triangle[1], values[2], values[1]);
      break;
    case 0b110:
      *result++ = triangle[0];
      *result++ = clip_intersect_edge(triangle[1], triangle[0], values[1], values[0]);
      *result++ = clip_intersect_edge(triangle[2], triangle[0], values[2], values[0]);
      break;
      break;
    case 0b111:
      break;
  }

  return result;
}

vertex* clip_triangle(vertex* begin, vertex* end){
  static vec4f_t const equations[2] = {
    {0.f, 0.f,  1.f, 1.f}, // Z > -W or  Z + w > 0
    {0.f, 0.f, -1.f, 1.f}, // Z <  W or -Z + W > 0
  };

  vertex result[12];

  for (int i = 0; i < 2; ++i){
    vertex* result_end = result;

    for (vertex* triangle = begin; triangle != end; triangle += 3){
      result_end = clip_triangle_single_plane(triangle, equations[i], result_end);
    }

    size_t num_bytes = (size_t)(result_end - result) * sizeof(vertex);
    if (num_bytes > 0){
      memcpy(begin, result, num_bytes);
    }

    end = begin + (result_end - result);
  }

  return end;
}

//color
color_t vec4f_to_color(vec4f_t v){
  uint8_t components[4] = {};

  for (int i = 0; i < 4; i++){
    components[i] = (uint8_t)(fmin(fmax(v.v[i], 0.f), 1.f) * 255.f);
  }

  return make_color(components[0], components[1], components[2], components[3]);
}

color_t make_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
  return (color_t)r |
         ((color_t)g << 8) |
         ((color_t)b << 16) |
         ((color_t)a << 24);
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
