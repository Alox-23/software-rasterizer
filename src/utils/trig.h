#ifndef TRIG_H
#define TRIG_H

#include "float.h"
#include <math.h>

#define LUT_SIZE 512
#define LUT_MASK (LUT_SIZE - 1)
#define INDEX_SCALE (LUT_SIZE * FIXED_SCALE)
#define M_PI 3.14159265359

static fixed_t sin_lut[LUT_SIZE];

void init_sin_lut();

fixed_t fixed_sin(fixed_t angle);
fixed_t fixed_cos(fixed_t angle);

fixed_t deg_to_fixed(float_t deg);
fixed_t fixed_sin_deg(float_t deg);
fixed_t fixed_cos_deg(float_t deg);

#endif
