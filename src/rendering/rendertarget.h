#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "viewport.h"
#include "colorbuffer.h"
#include "depthbuffer.h"

typedef struct{
  depth_buffer_t depth_buffer;
  color_buffer_t color_buffer;
  viewport_t viewport;
} render_target_t;

#endif
