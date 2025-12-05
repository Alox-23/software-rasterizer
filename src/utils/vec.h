#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
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

void print_vec4f(char* name, vec4f_t a);

//basic arithmetic
void add_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b); // returns a + b
void sub_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b); // returns a - b 
void mul_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, vec4f_t* restrict b); // returns a * b
void scl_vec4f(vec4f_t* restrict r, vec4f_t* restrict a, float s); // returns a * s

//complex funcitons
void neg_vec4f(vec4f_t* restrict r, vec4f_t* restrict a); // returns -a
float dot_vec4f(vec4f_t* restrict a, vec4f_t* restrict b); // return dot product of a, b
float mag_sq_vec4f(vec4f_t* restricta); // ONLY FOR VECTORS, magnitude of a vector squared
vec4f_t nrm_vec4f(vec4f_t* restrict a); // ONLY FOR VECTORS
void pdiv_vec4f(vec4f_t* restrict r, vec4f_t* restrict v);
float dst_sq_vec4f(vec4f_t* restricta, vec4f_t* restrict b); // distance between two POINTS squared
float det2d_vec4f(vec4f_t* restrict a, vec4f_t* restrict b); // the determinant of the vector along the XY plane (for drawring point-in-triangle test)
bool left_or_top_edge(vec4f_t* restrict start, vec4f_t* restrict end); // helps to remove overdraw in cases where triangle edges overlap

//utility functions
vec4f_t min_vec4f(vec4f_t a, vec4f_t b); // min of a, b
vec4f_t max_vec4f(vec4f_t a, vec4f_t b); // max of a, b
vec4f_t flr_vec4f(vec4f_t a); // floor a
vec4f_t cil_vec4f(vec4f_t a); // ciel a
vec4f_t abs_vec4f(vec4f_t a); // abs a


#endif
