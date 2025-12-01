#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

#include "viewport.h"
#include "colorbuffer.h"

typedef struct{
  color_buffer_t color_buffer;
  viewport_t viewport;
} render_target_t;

#endif
