#include "pixelbuffer.h"

void clear_pixel_buffer(pixel_buffer_t rb, color_t color){
  int size = rb.width * rb.height;  

  for (int i = 0; i < rb.width * rb.height; i++){
    rb.pixels[i] = color; // fill every pixel in black
  }
}

