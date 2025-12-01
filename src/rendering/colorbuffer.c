#include "colorbuffer.h"

void clear_color_buffer(color_buffer_t cb, vec4f_t color){
  int size = cb.width * cb.height;  
  
  color_t color_color = vec4f_to_color(color);

  for (int i = 0; i < cb.width * cb.height; i++){
    cb.pixels[i] = color_color;
  }
}

