#include "trig.h"
#include "float.h"
#include <math.h>

void init_sin_lut(){
  for (int i = 0; i < LUT_SIZE; i++){
    double angle = (double)i / LUT_SIZE * 2.0 * M_PI;
    sin_lut[i] = (fixed_t)(sin(angle) * FIXED_SCALE);
  }
}

fixed_t fixed_sin(fixed_t angle){
  angle &= FIXED_SCALE - 1;

  uint64_t position = ((uint64_t)angle * LUT_SIZE) >> FIXED_SHIFT;

  uint64_t index = position >> FIXED_SHIFT;
  fixed_t frac = (fixed_t)(position & (FIXED_SCALE - 1));

  //linear interpolation for accuracy
  fixed_t y0 = sin_lut[index & LUT_MASK];
  fixed_t y1 = sin_lut[(index + 1) & LUT_MASK];

  fixed_t diff = fixed_sub(y1, y0);
  fixed_t interp_part = fixed_mul(diff, frac);

  return fixed_add(y0, interp_part);
}

fixed_t fixed_cos(fixed_t angle){
  return fixed_sin(angle + (FIXED_SCALE / 4));
}

fixed_t deg_to_fixed(float_t deg){
  return float_to_fixed(deg / 360.0f);
}

fixed_t fixed_sin_deg(float_t deg){
  return fixed_sin(deg_to_fixed(deg));
}

fixed_t fixed_cos_deg(float_t deg){
  return fixed_cos(deg_to_fixed(deg));
}
