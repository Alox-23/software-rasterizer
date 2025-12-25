#include "cube.h"

static vec4f_t cube_positions[] = {
  // -X face
  {-1.f, -1.f, -1.f, 1.f},
  {-1.f,  1.f, -1.f, 1.f},
  {-1.f, -1.f,  1.f, 1.f},
  {-1.f,  1.f,  1.f, 1.f},

  // +X face
  { 1.f, -1.f, -1.f, 1.f},
  { 1.f,  1.f, -1.f, 1.f},
  { 1.f, -1.f,  1.f, 1.f},
  { 1.f,  1.f,  1.f, 1.f},

  // -Y face
  {-1.f, -1.f, -1.f, 1.f},
  { 1.f, -1.f, -1.f, 1.f},
  {-1.f, -1.f,  1.f, 1.f},
  { 1.f, -1.f,  1.f, 1.f},

  // +Y face
  {-1.f,  1.f, -1.f, 1.f},
  { 1.f,  1.f, -1.f, 1.f},
  {-1.f,  1.f,  1.f, 1.f},
  { 1.f,  1.f,  1.f, 1.f},

  // -Z face
  {-1.f, -1.f, -1.f, 1.f},
  { 1.f, -1.f, -1.f, 1.f},
  {-1.f,  1.f, -1.f, 1.f},
  { 1.f,  1.f, -1.f, 1.f},

  // +Z face
  {-1.f, -1.f,  1.f, 1.f},
  { 1.f, -1.f,  1.f, 1.f},
  {-1.f,  1.f,  1.f, 1.f},
  { 1.f,  1.f,  1.f, 1.f},
};

static vec4f_t cube_colors[] = {
  // -X face
  {1.f, 0.f, 0.f, 1.f},
  {0.f, 1.f, 0.f, 1.f},
  {0.f, 0.f, 1.f, 1.f},
  {0.f, 1.f, 1.f, 1.f},
  
  // X face
  {1.f, 0.f, 0.f, 1.f},
  {0.f, 1.f, 0.f, 1.f},
  {0.f, 0.f, 1.f, 1.f},
  {0.f, 1.f, 1.f, 1.f},
  
  // -Y face
  {1.f, 0.f, 0.f, 1.f},
  {0.f, 1.f, 0.f, 1.f},
  {0.f, 0.f, 1.f, 1.f},
  {0.f, 1.f, 1.f, 1.f},
  
  // Y face
  {1.f, 0.f, 0.f, 1.f},
  {0.f, 1.f, 0.f, 1.f},
  {0.f, 0.f, 1.f, 1.f},
  {0.f, 1.f, 1.f, 1.f},
  
  // -Z face
  {1.f, 0.f, 0.f, 1.f},
  {0.f, 1.f, 0.f, 1.f},
  {0.f, 0.f, 1.f, 1.f},
  {0.f, 1.f, 1.f, 1.f},
  
  // Z face
  {1.f, 0.f, 0.f, 1.f},
  {0.f, 1.f, 0.f, 1.f},
  {0.f, 0.f, 1.f, 1.f},
  {0.f, 1.f, 1.f, 1.f},
};

static uint32_t cube_indices[] = {
  // -X face
  0,  2,  1,
  1,  2,  3,

  // +X face
  4,  5,  6,
  6,  5,  7,

  // -Y face
  8,  9, 10,
  10,  9, 11,

  // +Y face
  12, 14, 13,
  14, 15, 13,

  // -Z face
  16, 18, 17,
  17, 18, 19,

  // +Z face
  20, 21, 22,
  21, 23, 22,
};

mesh_t make_cube_mesh(){
  mesh_t cube_mesh_example = {
    .positions = cube_positions,
    .colors = cube_colors,
    .indices = cube_indices,
    .count = 36,
  };

  return cube_mesh_example;
}
