#ifndef DEPTH_BUFFER_H
#define DEPTH_BUFFER_H

#include <stdlib.h>
#include <stdbool.h>
#include "../utils/utils.h"
#include "../core/core.h"

typedef enum{
  NEVER,
  ALWAYS,
  LESS,
  LESS_EQUAL,
  GREATER,
  GREATER_EQUAL,
  EQUAL,
  NOT_EQUAL,
} depth_test_t;

typedef struct{
  bool write;
  depth_test_t mode;
} depth_settings_t;

typedef struct{
  uint32_t* depth_values;
  uint32_t width;
  uint32_t height;
} depth_buffer_t;

void alloc_depth_buffer(depth_buffer_t* db, uint32_t width, uint32_t height);
void free_depth_buffer(depth_buffer_t* db);
void clear_depth_buffer(depth_buffer_t db, uint32_t value);
bool depth_test(depth_test_t mode, uint32_t value, uint32_t ref);

#endif
