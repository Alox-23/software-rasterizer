#include "viewport.h"

vec4f_t apply_viewport(viewport_t viewport, vec4f_t v){
  v.x = viewport.xmin + (viewport.xmax - viewport.xmin) * (0.5f + 0.5f * v.x);
  v.y = viewport.ymin + (viewport.ymax - viewport.ymin) * (0.5f - 0.5f * v.y);
  return v;
}
