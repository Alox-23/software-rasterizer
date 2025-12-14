#ifndef RCMD_H
#define RCMD_H

#include "mesh.h"
#include "depthbuffer.h"

typedef enum{
  NONE,
  CW,
  CCW,
}cull_mode_e;

typedef struct{
  mesh_t mesh;
  cull_mode_e cull_mode;
  depth_settings_t depth;
  mat4f_t transform;
}render_command_t;

#endif
