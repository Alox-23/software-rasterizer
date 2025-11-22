#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include "utils/utils.h"

int main(){
  init_sin_lut();

  printf("TESTING VECTOR AND FLOAT UTILS\n");
  printf("\nTRIGONOMETRY: \n");
  
  for (int i = 0; i < 360; i+=45){
    printf("\tsin of %d is (float_t)%.3f, (fixed_t) %d, real: %lf\n", i, fixed_to_float(fixed_sin(float_to_fixed(deg_to_rad(i)))), fixed_sin(float_to_fixed(deg_to_rad(i))), sin(deg_to_rad(i)));
    printf("\tcos of %d is (float_t)%.3f, (fixed_t) %d, real: %lf\n", i, fixed_to_float(fixed_cos(float_to_fixed(deg_to_rad(i)))), fixed_cos(float_to_fixed(deg_to_rad(i))), cos(deg_to_rad(i)));
  }

  printf("\nARITHMETIC :\n");

  float float_b;
  float float_a;

  printf("\tEnter value of A: ");
  scanf("%f", &float_a);

  printf("\tEnter value of B: ");
  scanf("%f", &float_b);

  fixed_t a = float_to_fixed(float_a);
  fixed_t b = float_to_fixed(float_b);

  printf("\tADDITION:\n");
  printf("\t\tFIXED: (%d)+(%d) = %d\n", a, b, fixed_add(a, b));
  printf("\t\tFLOAT: (%f)+(%f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_add(a, b)));
  printf("\t\tREALF: (%f)+(%f) = %f\n", float_a, float_b, float_a + float_b);
  
  printf("\tSUBTRACTION:\n");
  printf("\t\tFIXED: (%d)+(%d) = %d\n", a, b, fixed_sub(a, b));
  printf("\t\tFLOAT: (%f)+(%f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_sub(a, b)));
  printf("\t\tREALF: (%f)+(%f) = %f\n", float_a, float_b, float_a - float_b);

  printf("\tMULTIPLICATION:\n");
  printf("\t\tFIXED: (%d)+(%d) = %d\n", a, b, fixed_mul(a, b));
  printf("\t\tFLOAT: (%f)+(%f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_mul(a, b)));
  printf("\t\tREALF: (%f)+(%f) = %f\n", float_a, float_b, float_a * float_b);

  printf("\tDIVISION:\n");
  printf("\t\tFIXED: (%d)+(%d) = %d\n", a, b, fixed_div(a, b));
  printf("\t\tFLOAT: (%f)+(%f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_div(a, b)));
  printf("\t\tREALF: (%f)+(%f) = %f\n", float_a, float_b, float_a / float_b);

  printf("\tROOT OF A:\n");
  printf("\t\tFIXED: root(%d) = %d\n", a, fixed_sqrt(a));
  printf("\t\tFLOAT: root(%f) = %f\n", fixed_to_float(a), fixed_to_float(fixed_sqrt(a)));
  printf("\t\tREALF: root(%f) = %f\n", float_a, sqrt(float_a));
  
  printf("\tPOW OF 2 A:\n");
  printf("\t\tFIXED: (%d)**2 = %d\n", a, fixed_ex2(a));
  printf("\t\tFLOAT: (%f)**2 = %f\n", fixed_to_float(a), fixed_to_float(fixed_ex2(a)));
  printf("\t\tREALF: (%f)**2 = %f\n", float_a, float_a*float_a);
  
  printf("\tABS OF A:\n");
  printf("\t\tFIXED: (%d)**2 = %d\n", a, fixed_abs(a));
  printf("\t\tFLOAT: (%f)**2 = %f\n", fixed_to_float(a), fixed_to_float(fixed_abs(a)));
  printf("\t\tREALF: (%f)**2 = %f\n", float_a, fabs(float_a));
  
  printf("\tFLOOR OF A:\n");
  printf("\t\tFIXED: (%d)**2 = %d\n", a, fixed_flr(a));
  printf("\t\tFLOAT: (%f)**2 = %f\n", fixed_to_float(a), fixed_to_float(fixed_flr(a)));
  printf("\t\tREALF: (%f)**2 = %f\n", float_a, floor(float_a));
 
  printf("\tCIEL OF A:\n");
  printf("\t\tFIXED: root(%d) = %d\n", a, fixed_cil(a));
  printf("\t\tFLOAT: root(%f) = %f\n", fixed_to_float(a), fixed_to_float(fixed_cil(a)));
  printf("\t\tREALF: root(%f) = %f\n", float_a, ceil(float_a));
   
  return 0;
}
