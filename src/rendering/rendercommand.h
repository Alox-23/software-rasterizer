#ifndef RCMD_H
#define RCMD_H

#include "mesh.h"

typedef enum{
  NONE,
  CW,
  CCW,
}cull_mode_e;

typedef struct{
  mesh_t mesh;
  cull_mode_e cull_mode;
  mat4f_t transform;
}render_command_t;

#endif
