#include "float.h"

fixed_t float_to_fixed(float n){
  return (fixed_t)(n * FIXED_SCALE);
}

float fixed_to_float(fixed_t n){
  return (float)n / (float)FIXED_SCALE;
}

int32_t fixed_to_int(fixed_t n){
  return (n + (FIXED_SCALE / 2)) >> FIXED_SHIFT;
}

fixed_t fixed_add(fixed_t a, fixed_t b){
  return a + b;
}

fixed_t fixed_sub(fixed_t a, fixed_t b){
  return a - b;
}

fixed_t fixed_mul(fixed_t a, fixed_t b){
  int64_t temp = (int64_t)a * (int64_t)b;
  return (fixed_t)(temp >> FIXED_SHIFT);
}

fixed_t fixed_div(fixed_t a, fixed_t b){
  if (b == 0){
    return (a >= 0) ? INT32_MAX : INT32_MIN;
  }
  int64_t temp = ((int64_t)a << FIXED_SHIFT);
  return (fixed_t)(temp / b);
}

fixed_t fixed_sqrt(fixed_t N){
  if (N <= 0) return 0;

  fixed_t x_n = ONE_F;

  for (int i = 0; i < 4; i++){
    fixed_t N_over_xn = fixed_div(N, x_n);

    fixed_t sum = fixed_add(x_n, N_over_xn);
    
    x_n += (sum >> 1); // half of sum
  }

  return x_n;
}

fixed_t fixed_abs(fixed_t n){
  return (n < 0) ? -n : n;
}

fixed_t fixed_min(fixed_t a, fixed_t b){
  return (a < b) ? a : b;
}

fixed_t fixed_max(fixed_t a, fixed_t b){
  return (a < b) ? a : b;
}

fixed_t fixed_ex2(fixed_t a){
  return fixed_mul(a, a);
}

fixed_t fixed_flr(fixed_t a){
  if (a >= 0){
    return a & ~(FIXED_SCALE - 1);
  } else {
    return -fixed_cil(-a);
  }
}

fixed_t fixed_cil(fixed_t a){
  if (a >= 0){
    return (a + (FIXED_SCALE - 1)) & ~(FIXED_SCALE - 1);
  } else {
    return -fixed_flr(-a);
  }
}
