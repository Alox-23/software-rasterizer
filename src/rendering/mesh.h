#ifndef MESH_H
#define MESH_H

#include "../utils/utils.h"

//stores points in 3d space
//number of triangles in mesh = positions / vertex_count
typedef struct{
  vec4f_t* positions;
  vec4f_t* colors; 
  uint32_t vertex_count;
}mesh_t;

mesh_t make_mesh();

#endif
