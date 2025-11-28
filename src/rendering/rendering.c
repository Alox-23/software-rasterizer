#include "rendering.h"

void render_draw_call(pixel_buffer_t *pixl_buff, render_command_t command){
  for (uint32_t vertex_index = 0; vertex_index + 2 < command.mesh.vertex_count; vertex_index += 3){
    vec4f_t v0 = command.mesh.positions[vertex_index + 0]; 
    vec4f_t v1 = command.mesh.positions[vertex_index + 1]; 
    vec4f_t v2 = command.mesh.positions[vertex_index + 2];

    for (int32_t y = 0; y < pixl_buff->height; ++y){
      for (int32_t x = 0; x < pixl_buff->width; ++x){
        vec4f_t p = {x + 0.5f, y + 0.5f, 0.f, 0.f};

        float det_v0_v1 = det2d_vec4f(sub_vec4f(v1, v0), sub_vec4f(p, v0));
        float det_v1_v2 = det2d_vec4f(sub_vec4f(v2, v1), sub_vec4f(p, v1));
        float det_v2_v0 = det2d_vec4f(sub_vec4f(v0, v2), sub_vec4f(p, v2));
      
        if (det_v0_v1 >= 0.f && det_v1_v2 >= 0.f && det_v2_v0 >= 0.f){
          pixl_buff->pixels[x + y * pixl_buff->width] = vec4f_to_color(command.mesh.color);
        }
      }
    }
  }
}
