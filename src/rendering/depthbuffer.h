#ifndef DEPTH_BUFFER_H
#define DEPTH_BUFFER_H

#include "stdlib.h"
#include "../utils/utils.h"
#include "../core/core.h"

typedef struct{
  uint32_t* depth_values;
  uint32_t width;
  uint32_t height;
} depth_buffer_t;

void alloc_depth_buffer(depth_buffer_t* db, uint32_t width, uint32_t height);
void free_depth_buffer(depth_buffer_t* db);

#endif
