#ifndef RBUFF_H
#define RBUFF_H

#include "../utils/utils.h"

//buffer used to acces pixel data
typedef struct{
  color_t* pixels;
  uint32_t width;
  uint32_t height;
}render_buffer_t;

void clear_render_buffer(render_buffer_t rb, color_t color){
  for (int i = 0; i < rb.width * rb.height; i++){
    rb.pixels[i] = color; // fill every pixel in black
  }
}

#endif
