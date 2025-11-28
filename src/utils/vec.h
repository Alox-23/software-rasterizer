#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>

//x and v[0] share the same memory location 
//so they are the same variable that can be assesed by different identifiers
//w = 0 means its a direction vector 
//w = 1 means its a point in 3d space
//so, point - vector = vector
//and other stuff
typedef union{
  struct{
    float x, y, z, w;
  };
  float v[4];
} vec4f_t;

typedef uint32_t color_t;

void print_vec4f(char* name, vec4f_t a);
vec4f_t make_vec4f(float x, float y, float z, float w);

//color
color_t vec4f_to_color(vec4f_t v);
color_t make_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
uint8_t get_r(color_t c);
uint8_t get_g(color_t c);
uint8_t get_b(color_t c);
uint8_t get_a(color_t c);
void set_r(color_t *c, uint8_t new_value);
void set_g(color_t *c, uint8_t new_value);
void set_b(color_t *c, uint8_t new_value);
void set_a(color_t *c, uint8_t new_value);

//basic arithmetic
vec4f_t add_vec4f(vec4f_t a, vec4f_t b); // returns a + b
vec4f_t sub_vec4f(vec4f_t a, vec4f_t b); // returns a - b 
vec4f_t mul_vec4f(vec4f_t a, vec4f_t b); // returns a * b
vec4f_t scl_vec4f(vec4f_t a, float s); // returns a * s

//complex funcitons
vec4f_t neg_vec4f(vec4f_t a); // returns -a
float dot_vec4f(vec4f_t a, vec4f_t b); // return dot product of a, b
float mag_sq_vec4f(vec4f_t a); // ONLY FOR VECTORS, magnitude of a vector squared
vec4f_t nrm_vec4f(vec4f_t a); // ONLY FOR VECTORS
float dst_sq_vec4f(vec4f_t a, vec4f_t b); // distance between two POINTS squared
float det2d_vec4f(vec4f_t a, vec4f_t b); // the determinant of the vector along the XY plane (for drawring point-in-triangle test)

//utility functions
vec4f_t min_vec4f(vec4f_t a, vec4f_t b); // min of a, b
vec4f_t max_vec4f(vec4f_t a, vec4f_t b); // max of a, b
vec4f_t flr_vec4f(vec4f_t a); // floor a
vec4f_t cil_vec4f(vec4f_t a); // ciel a
vec4f_t abs_vec4f(vec4f_t a); // abs a


#endif
