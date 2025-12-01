#ifndef RBUFF_H
#define RBUFF_H

#include "../utils/utils.h"

//buffer used to acces pixel data
typedef struct{
  color_t* pixels;
  uint32_t width;
  uint32_t height;
}color_buffer_t;

void clear_color_buffer(color_buffer_t cb, vec4f_t color);

#endif
