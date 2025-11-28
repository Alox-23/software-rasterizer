#ifndef RBUFF_H
#define RBUFF_H

#include "../utils/utils.h"

//buffer used to acces pixel data
typedef struct{
  color_t* pixels;
  uint32_t width;
  uint32_t height;
}pixel_buffer_t;

void clear_pixel_buffer(pixel_buffer_t pb, color_t color);

#endif
