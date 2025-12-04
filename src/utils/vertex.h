#ifndef VERTEX_H
#define VERTEX_H

#include <string.h>
#include <stdlib.h>
#include "vec.h"

typedef struct{
  vec4f_t position;
  vec4f_t color;
} vertex;

vertex clip_intersect_edge(vertex const v0, vertex const v1, float value0, float value1);
vertex* clip_triangle_single_plane(vertex* triangle, vec4f_t equation, vertex* result);
vertex* clip_triangle(vertex* begin, vertex* end);

#endif
