#include "float.h"

fixed_t float_to_fixed(float_t n){
  return (fixed_t)(n * FIXED_SCALE);
}

float_t fixed_to_float(fixed_t n){
  return (float_t)n / (float_t)FIXED_SCALE;
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

fixed_t fixed_abs(fixed_t n){
  return (n < 0) ? -n : n;
}

fixed_t fixed_min(fixed_t a, fixed_t b){
  return (a < b) ? a : b;
}

fixed_t fixed_max(fixed_t a, fixed_t b){
  return (a < b) ? a : b;
}
