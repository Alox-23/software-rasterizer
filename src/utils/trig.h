#ifndef TRIG_H
#define TRIG_H

#include "float.h"
#include <math.h>

#define LUT_SIZE 512
#define LUT_MASK (LUT_SIZE - 1)
#define PI 3.14159265359
#define TWO_PI (PI * 2)
#define PI_F (PI * FIXED_SCALE)
#define TWO_PI_F (fixed_t)(PI * 2 * FIXED_SCALE)
#define PI_RATIO (PI / 180.f)

static fixed_t sin_lut[LUT_SIZE];

void init_sin_lut();

fixed_t fixed_sin(fixed_t radians);
fixed_t fixed_cos(fixed_t radians);

float_t deg_to_rad(float deg);
float_t rad_to_deg(float rad);

#endif
