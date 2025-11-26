#include "trig.h"
#include "float.h"
#include <math.h>

void init_sin_lut(){
  for (int i = 0; i < LUT_SIZE; i++){
    double angle = (double)i / LUT_SIZE * TWO_PI;
    sin_lut[i] = (fixed_t)(float_to_fixed(sin(angle))); // store fixed-point floats in the sin_lut array 
  }
}

fixed_t fixed_sin(fixed_t radians){
  radians %= TWO_PI_F;

  uint32_t index = (radians * LUT_SIZE) / TWO_PI_F;

  index &= (LUT_MASK);

  return sin_lut[index];
}

float_t deg_to_rad(float_t deg){
  return deg * (PI_RATIO); 
}

float_t rad_to_deg(float_t rad){
  return rad / (PI_RATIO); 
}

fixed_t fixed_cos(fixed_t radians){
  return fixed_sin(radians + HALF_PI_F); // + 0.5pi in fixed format to convert to cos
}
