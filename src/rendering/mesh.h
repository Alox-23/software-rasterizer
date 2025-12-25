#ifndef MESH_H
#define MESH_H

#include "../utils/utils.h"
#include "../core/core.h"
#include <stdlib.h>

//stores points in 3d space
//number of triangles in mesh = count / 3
typedef struct{
  vec4f_t* positions;
  vec4f_t* colors;
  uint32_t *indices;
  uint32_t count;
}mesh_t;

mesh_t* load_mesh_from_file(const char* filename, vec4f_t color, mat4f_t transform);
void free_mesh();

#endif
