#include "pixelbuffer.h"

void clear_pixel_buffer(pixel_buffer_t pb, color_t color){
  int size = pb.width * pb.height;  

  for (int i = 0; i < pb.width * pb.height; i++){
    pb.pixels[i] = color; // fill every pixel in black
  }
}

