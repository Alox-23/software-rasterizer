#include "color.h"

//color
color_t vec4f_to_color(vec4f_t v){
  uint8_t components[4] = {};

  for (int i = 0; i < 4; i++){
    components[i] = (uint8_t)(fmin(fmax(v.v[i], 0.f), 1.f) * 255.f);
  }

  return make_color(components[0], components[1], components[2], components[3]);
}

color_t make_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
  return (color_t)r |
         ((color_t)g << 8) |
         ((color_t)b << 16) |
         ((color_t)a << 24);
}

uint8_t get_r(color_t c){
  return (uint8_t)(c & 0xFF);
}

uint8_t get_g(color_t c){
  return (uint8_t)((c >> 8) & 0xFF);
}

uint8_t get_b(color_t c){
  return (uint8_t)((c >> 16) & 0xFF);
}

uint8_t get_a(color_t c){
  return (uint8_t)((c >> 24) & 0xFF);
}

void set_r(color_t *c, uint8_t new_val){
  *c = (*c & ~0xFF) | new_val;
}

void set_g(color_t *c, uint8_t new_val){
  *c = (*c & ~(0xFF << 8)) | ((color_t)new_val << 8);
}

void set_b(color_t *c, uint8_t new_val){
  *c = (*c & ~(0xFF << 16)) | ((color_t)new_val << 16);
}

void set_a(color_t *c, uint8_t new_val){
  *c = (*c & ~(0xFF << 24)) | ((color_t)new_val << 24);
}
