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
  printf("\t\tFIXED: fabs(%d) = %d\n", a, fixed_abs(a));
  printf("\t\tFLOAT: fabs(%f) = %f\n", fixed_to_float(a), fixed_to_float(fixed_abs(a)));
  printf("\t\tREALF: fabs(%f) = %f\n", float_a, fabs(float_a));
  
  printf("\tFLOOR OF A:\n");
  printf("\t\tFIXED: floor(%d) = %d\n", a, fixed_flr(a));
  printf("\t\tFLOAT: floor(%f) = %f\n", fixed_to_float(a), fixed_to_float(fixed_flr(a)));
  printf("\t\tREALF: floor(%f) = %f\n", float_a, floor(float_a));
 
  printf("\tCEIL OF A:\n");
  printf("\t\tFIXED: ceil(%d) = %d\n", a, fixed_cil(a));
  printf("\t\tFLOAT: ceil(%f) = %f\n", fixed_to_float(a), fixed_to_float(fixed_cil(a)));
  printf("\t\tREALF: ceil(%f) = %f\n", float_a, ceil(float_a));
   
  printf("\tMIN:\n");
  printf("\t\tFIXED: min(%d, %d) = %d\n", a, b, fixed_min(a, b));
  printf("\t\tFLOAT: min(%f, %f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_min(a, b)));
  printf("\t\tREALF: min(%f, %f) = %f\n", float_a, float_b, (float_a < float_b) ? float_a : float_b);
 
  printf("\tMAX:\n");
  printf("\t\tFIXED: max(%d, %d) = %d\n", a, b, fixed_max(a, b));
  printf("\t\tFLOAT: max(%f, %f) = %f\n", fixed_to_float(a), fixed_to_float(b), fixed_to_float(fixed_max(a, b)));
  printf("\t\tREALF: max(%f, %f) = %f\n", float_a, float_b, (float_a > float_b) ? float_a : float_b);
  
  printf("\nVECTORS :\n");

  float float_ax;
  float float_ay;
  float float_az;
  float float_aw;

  float float_bx;
  float float_by;
  float float_bz;
  float float_bw;
  
  printf("\tEnter value of Ax: ");
  scanf("%f", &float_ax);
  printf("\tEnter value of Ay: ");
  scanf("%f", &float_ay);
  printf("\tEnter value of Az: ");
  scanf("%f", &float_az);
  printf("\tEnter value of Aw: ");
  scanf("%f", &float_aw);

  printf("\tEnter value of Bx: ");
  scanf("%f", &float_bx);
  printf("\tEnter value of By: ");
  scanf("%f", &float_by);
  printf("\tEnter value of Bz: ");
  scanf("%f", &float_bz);
  printf("\tEnter value of Bw: ");
  scanf("%f", &float_bw);

  vec4f_t A = {float_to_fixed(float_ax), float_to_fixed(float_ay), float_to_fixed(float_az), float_to_fixed(float_aw)};
  vec4f_t B = {float_to_fixed(float_bx), float_to_fixed(float_by), float_to_fixed(float_bz), float_to_fixed(float_bw)};
 
  printf("\tYour Vectors:\n");
  print_vec4f("\t\tA", A);
  print_vec4f("\t\tB", B);

  printf("\tADDITION\n");
  vec4f_t sum_of_AB = add_vec4f(A, B);
  print_vec4f("\t\tA+B", sum_of_AB);

  printf("\tSUBTRACTION\n");
  vec4f_t sub_of_AB = sub_vec4f(A, B);
  print_vec4f("\t\tA-B", sub_of_AB);

  printf("\tMULTIPICATION\n");
  vec4f_t prd_of_AB = mul_vec4f(A, B);
  print_vec4f("\t\tA*B", prd_of_AB);

  printf("\tSCALE BY 0.5\n");
  vec4f_t scl_of_A = scl_vec4f(A, float_to_fixed(0.5f));
  print_vec4f("\t\tA*0.5", scl_of_A);

  printf("\tNEGATE A\n");
  vec4f_t neg_of_A = neg_vec4f(A);
  print_vec4f("\t\tA+B", neg_of_A);

  printf("\tDOT PRODUCT OF AB\n");
  fixed_t dot_of_AB = dot_vec4f(A, B);
  printf("\t\tAB = %f\n", fixed_to_float(dot_of_AB));

  printf("\tMAGNITUDE OF A\n");
  fixed_t mag_of_A = mag_sq_vec4f(A);
  printf("\t\tAm = %f\n", fixed_to_float(mag_of_A));

  printf("\tNORMAL OF A\n");
  vec4f_t nrm_of_A = nrm_vec4f(A);
  print_vec4f("\t\tA*0.5", nrm_of_A);
  
  printf("\tDIST BETWEEN A AND B\n");
  fixed_t dist_AB = dst_sq_vec4f(A, B);
  printf("\t\tA to B = %f\n", fixed_to_float(dist_AB));

  return 0;
}
