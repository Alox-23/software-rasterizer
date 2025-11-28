#include "rendering.h"

void render_call(pixel_buffer_t *pixl_buff, render_command_t command){
  for (uint32_t vertex_index = 0; vertex_index + 2 < command.mesh.vertex_count; vertex_index += 3){
    vec4f_t v0 = command.mesh.positions[vertex_index + 0]); 
    vec4f_t v1 = command.mesh.positions[vertex_index + 1]); 
    vec4f_t v2 = command.mesh.positions[vertex_index + 2]);

    for (int32_t y = 0; y < color_buffer.height; ++y){
      for (int32_t x = 0; x < color_buffer.width; ++x){
        vec4f_t p = {};
      }
    }
  }
}
