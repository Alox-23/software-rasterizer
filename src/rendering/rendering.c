#include "rendering.h"

void render_draw_call(pixel_buffer_t *pixl_buff, render_command_t command){
  for (uint32_t vertex_index = 0; vertex_index + 2 < command.mesh.vertex_count; vertex_index += 3){
    /*
    vec4f_t v0 = command.mesh.positions[vertex_index + 0]; 
    vec4f_t v1 = command.mesh.positions[vertex_index + 1]; 
    vec4f_t v2 = command.mesh.positions[vertex_index + 2]; 
    */
    vec4f_t v0 = mul_matvec4f(command.transform, command.mesh.positions[vertex_index + 0]); 
    vec4f_t v1 = mul_matvec4f(command.transform, command.mesh.positions[vertex_index + 1]); 
    vec4f_t v2 = mul_matvec4f(command.transform, command.mesh.positions[vertex_index + 2]); 

    /*
    print_vec4f("v0", v0);
    print_vec4f("v1", v1);
    print_vec4f("v2", v2);
    */

    //handling triangle orientation
    //if determinant v0, v1, v2 is < 0 we need to swap v1 and v2

    float det_v0_v1_v2 = det2d_vec4f(sub_vec4f(v1, v0), sub_vec4f(v2, v0));
    const bool is_ccw = det_v0_v1_v2 < 0.f;

    //handle culling
    switch (command.cull_mode){
      case NONE:
        break; //render the triangle
      case CW:
        if (!is_ccw) continue; //skip rendering
        break;
      case CCW:
        if (is_ccw) continue; //skip rendering
        break;
    }

    if (is_ccw){
      vec4f_t temp = v1;
      v1 = v2;
      v2 = temp;
    }

    vec4f_t edge_v0_v1 = sub_vec4f(v1, v0);
    vec4f_t edge_v1_v2 = sub_vec4f(v2, v1);
    vec4f_t edge_v2_v0 = sub_vec4f(v0, v2);

    int32_t xmin = fmin(v0.x, fmin(v1.x, v2.x));
    int32_t xmax = fmax(v0.x, fmax(v1.x, v2.x));
    int32_t ymin = fmin(v0.y, fmin(v1.y, v2.y));
    int32_t ymax = fmax(v0.y, fmax(v1.y, v2.y));

    for (int32_t y = ymin; y < ymax; ++y){
      uint32_t row_offset = y * pixl_buff->width;
      
      for (int32_t x = xmin; x < xmax; ++x){
        vec4f_t p = {x + 0.5f, y + 0.5f, 0.f, 0.f};

        float det_v0_v1_p = det2d_vec4f(edge_v0_v1, sub_vec4f(p, v0));
        float det_v1_v2_p = det2d_vec4f(edge_v1_v2, sub_vec4f(p, v1));
        float det_v2_v0_p = det2d_vec4f(edge_v2_v0, sub_vec4f(p, v2));

        //eliminates overdraw
        //if (left_or_top_edge(v0, v1)) det_v0_v1_p--; 
        //if (left_or_top_edge(v1, v2)) det_v1_v2_p--; 
        //if (left_or_top_edge(v2, v0)) det_v2_v0_p--; 
      
        if (det_v0_v1_p >= 0.f && det_v1_v2_p >= 0.f && det_v2_v0_p >= 0.f){
          pixl_buff->pixels[x + row_offset] = vec4f_to_color(command.mesh.color);
        }
      }
    }
  }
}
