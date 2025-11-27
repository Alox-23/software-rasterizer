#include "renderbuffer.h"

void clear_render_buffer(render_buffer_t rb, color_t color){
  int size = rb.width * rb.height;  

  for (int i = 0; i < rb.width * rb.height; i++){
    rb.pixels[i] = color; // fill every pixel in black
  }
}

