#include "vertex.h"

vertex clip_intersect_edge(vertex const v0, vertex const v1, float value0, float value1){
  float t = value0 / (value0 - value1);

  vertex v;
  v.position = add_vec4f(scl_vec4f(v0.position, (1.f - t)), scl_vec4f(v1.position, t));
  v.color = add_vec4f(scl_vec4f(v0.color, (1.f - t)), scl_vec4f(v1.color, t));

  return v;
}

vertex* clip_triangle_single_plane(vertex* triangle, vec4f_t equation, vertex* result){
  float values[3] = {
    dot_vec4f(triangle[0].position, equation),
    dot_vec4f(triangle[1].position, equation),
    dot_vec4f(triangle[2].position, equation),
  };

  uint8_t mask = (values[0] < 0.f ? 1 : 0) | (values[1] < 0.f ? 2 : 0) | (values[2] < 0.f ? 4 : 0);

  switch (mask){
    case 0b000:
      *result++ = triangle[0];
      *result++ = triangle[1];
      *result++ = triangle[2];
      break;
    case 0b001:
      vertex v01 = clip_intersect_edge(triangle[0], triangle[1], values[0], values[1]);
      vertex v02 = clip_intersect_edge(triangle[0], triangle[2], values[0], values[2]);
      *result++ = v01;
      *result++ = triangle[1];
      *result++ = triangle[2];
      *result++ = v01;
      *result++ = triangle[2];
      *result++ = v02;
      break;
    case 0b010:
      vertex v10 = clip_intersect_edge(triangle[1], triangle[0], values[1], values[0]);
      vertex v12 = clip_intersect_edge(triangle[1], triangle[2], values[1], values[2]);
      *result++ = triangle[0];
      *result++ = v10;
      *result++ = triangle[2];
      *result++ = triangle[2];
      *result++ = v10;
      *result++ = v12;
      break;
    case 0b011:
      *result++ = clip_intersect_edge(triangle[0], triangle[2], values[0], values[2]);
      *result++ = clip_intersect_edge(triangle[1], triangle[2], values[1], values[2]);
      *result++ = triangle[2];
      break;
    case 0b100:
      vertex v20 = clip_intersect_edge(triangle[2], triangle[0], values[2], values[0]);
      vertex v21 = clip_intersect_edge(triangle[2], triangle[1], values[2], values[1]);
      *result++ = triangle[0];
      *result++ = triangle[1];
      *result++ = v20;
      *result++ = v20;
      *result++ = triangle[1];
      *result++ = v21;
      break;
    case 0b101:
      *result++ = clip_intersect_edge(triangle[0], triangle[1], values[0], values[1]);
      *result++ = triangle[1];
      *result++ = clip_intersect_edge(triangle[2], triangle[1], values[2], values[1]);
      break;
    case 0b110:
      *result++ = triangle[0];
      *result++ = clip_intersect_edge(triangle[1], triangle[0], values[1], values[0]);
      *result++ = clip_intersect_edge(triangle[2], triangle[0], values[2], values[0]);
      break;
      break;
    case 0b111:
      break;
  }

  return result;
}

vertex* clip_triangle(vertex* begin, vertex* end){
  static vec4f_t const equations[2] = {
    {0.f, 0.f,  1.f, 1.f}, // Z > -W or  Z + w > 0
    {0.f, 0.f, -1.f, 1.f}, // Z <  W or -Z + W > 0
  };

  vertex result[12];

  for (int i = 0; i < 2; ++i){
    vertex* result_end = result;

    for (vertex* triangle = begin; triangle != end; triangle += 3){
      result_end = clip_triangle_single_plane(triangle, equations[i], result_end);
    }

    size_t num_bytes = (size_t)(result_end - result) * sizeof(vertex);
    if (num_bytes > 0){
      memcpy(begin, result, num_bytes);
    }

    end = begin + (result_end - result);
  }

  return end;
}
