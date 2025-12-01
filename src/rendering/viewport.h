#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "../utils/utils.h"

typedef struct{
  int32_t xmin, ymin, xmax, ymax;
} viewport_t;

vec4f_t apply_viewport(viewport_t viewport, vec4f_t v);

#endif
