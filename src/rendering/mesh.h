#ifndef MESH_H
#define MESH_H

#include "../utils/utils.h"

//stores points in 3d space
//number of triangles in mesh = positions / vertex_count
typedef struct{
  vec4f_t* positions;
  vec4f_t* colors;
  const uint32_t *indices;
  uint32_t count;
}mesh_t;

mesh_t make_mesh();

#endif
