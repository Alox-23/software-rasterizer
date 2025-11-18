#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include "utils/utils.h"

int main(){
  init_sin_lut();

  for (int i = 0; i < 360; i+=10){
    printf("sin of %d is (float_t)%.3f, (fixed_t) %d, real: %lf\n", i, fixed_to_float(fixed_sin(float_to_fixed(deg_to_rad(i)))), fixed_sin(float_to_fixed(deg_to_rad(i))), sin(deg_to_rad(i)));
  }

  fixed_t b = float_to_fixed(1.1f);
  fixed_t a = float_to_fixed(1.1f);

  printf("a(%d)+b(%d) = %d\n", a, b, fixed_add(a, b));
  printf("a(%f)+b(%f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_add(a, b)));

  return 0;
}
