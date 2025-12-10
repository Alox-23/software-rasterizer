#include "rendering.h"

void render_draw_call(render_target_t render_target, render_command_t command){
  for (uint32_t vertex_index = 0; vertex_index + 2 < command.mesh.count; vertex_index += 3){
    uint32_t i0 = vertex_index + 0;
    uint32_t i1 = vertex_index + 1;
    uint32_t i2 = vertex_index + 2;

    if (command.mesh.indices){
      i0 = command.mesh.indices[i0];
      i1 = command.mesh.indices[i1];
      i2 = command.mesh.indices[i2];
    }
    
    vertex clipped_vertices[12]; // stores all of the atributes of a trianlge, for them to be later be cliped
    
    clipped_vertices[0].position = mul_matvec4f(command.transform, command.mesh.positions[i0]);
    clipped_vertices[1].position = mul_matvec4f(command.transform, command.mesh.positions[i1]);
    clipped_vertices[2].position = mul_matvec4f(command.transform, command.mesh.positions[i2]);

    clipped_vertices[0].color = command.mesh.colors[i0];
    clipped_vertices[1].color = command.mesh.colors[i1];  
    clipped_vertices[2].color = command.mesh.colors[i2];

    vertex* clipped_vertices_end = clip_triangle(clipped_vertices, clipped_vertices + 3);
    
    for (vertex* triangle_begin = clipped_vertices; triangle_begin != clipped_vertices_end; triangle_begin += 3){
           
      vec4f_t v0 = triangle_begin[0].position; 
      vec4f_t v1 = triangle_begin[1].position; 
      vec4f_t v2 = triangle_begin[2].position; 

      v0 = pdiv_vec4f(v0);
      v1 = pdiv_vec4f(v1);
      v2 = pdiv_vec4f(v2);

      v0 = apply_viewport(render_target.viewport, v0);
      v1 = apply_viewport(render_target.viewport, v1);
      v2 = apply_viewport(render_target.viewport, v2);

      vec4f_t c0 = triangle_begin[0].color;
      vec4f_t c1 = triangle_begin[1].color;
      vec4f_t c2 = triangle_begin[2].color;
       
      //handling triangle orientation
      //if determinant v0, v1, v2 is < 0 we need to swap v1 and v2
      float det_v0_v1_v2 = det2d_vec4f(sub_vec4f(v1, v0), sub_vec4f(v2, v0));
      const bool is_ccw = det_v0_v1_v2 < 0.f;
      if (is_ccw){
        vec4f_t temp = v1;
        v1 = v2;
        v2 = temp;
        temp = c1;
        c1 = c2;
        c2 = temp;
      }
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
      
      vec4f_t edge_v0_v1 = {};
      vec4f_t edge_v1_v2 = {};
      vec4f_t edge_v2_v0 = {};

      vec4f_t edge_v0_p = {};
      vec4f_t edge_v1_p = {};
      vec4f_t edge_v2_p = {};

      psub_vec4f(&edge_v0_v1, &v1, &v0);
      psub_vec4f(&edge_v1_v2, &v2, &v1);
      psub_vec4f(&edge_v2_v0, &v0, &v2);

      int32_t xmin = fmax(render_target.viewport.xmin, 0);
      int32_t xmax = fmin(render_target.viewport.xmax, render_target.color_buffer.width);
      int32_t ymin = fmax(render_target.viewport.ymin, 0);
      int32_t ymax = fmin(render_target.viewport.ymax, render_target.color_buffer.height);

      xmin = fmax(0, fmin(v0.x, fmin(v1.x, v2.x)));
      xmax = fmin(render_target.color_buffer.width, fmax(v0.x, fmax(v1.x, v2.x)));
      ymin = fmax(0, fmin(v0.y, fmin(v1.y, v2.y)));
      ymax = fmin(render_target.color_buffer.height, fmax(v0.y, fmax(v1.y, v2.y)));

      for (int32_t y = ymin; y < ymax; ++y){
        uint32_t row_offset = y * render_target.color_buffer.width;
        
        for (int32_t x = xmin; x < xmax; ++x){
          vec4f_t p = {x + 0.5f, y + 0.5f, 0.f, 0.f};

          psub_vec4f(&edge_v0_p, &p, &v0);
          psub_vec4f(&edge_v1_p, &p, &v1);
          psub_vec4f(&edge_v2_p, &p, &v2);

          float det_v0_v1_p = det2d_vec4f(edge_v0_v1, edge_v0_p);
          float det_v1_v2_p = det2d_vec4f(edge_v1_v2, edge_v1_p);
          float det_v2_v0_p = det2d_vec4f(edge_v2_v0, edge_v2_p);

          //eliminates overdraw
          //if (left_or_top_edge(v0, v1)) det_v0_v1_p--; 
          //if (left_or_top_edge(v1, v2)) det_v1_v2_p--; 
          //if (left_or_top_edge(v2, v0)) det_v2_v0_p--; 
        
          if (det_v0_v1_p >= 0.f && det_v1_v2_p >= 0.f && det_v2_v0_p >= 0.f){
            float l0 = det_v1_v2_p / det_v0_v1_v2 / v0.w;
            float l1 = det_v2_v0_p / det_v0_v1_v2 / v1.w;
            float l2 = det_v0_v1_p / det_v0_v1_v2 / v2.w;

            float lsum = l0 + l1 + l2;

            l0 /= lsum;
            l1 /= lsum;
            l2 /= lsum;

            vec4f_t c0l0 = {};
            vec4f_t c1l1 = {};
            vec4f_t c2l2 = {};

            pscl_vec4f(&c0l0, &c0, l0);
            pscl_vec4f(&c1l1, &c1, l1);
            pscl_vec4f(&c2l2, &c2, l2);

            vec4f_t c1l1_c2l2 = {};

            padd_vec4f(&c1l1_c2l2, &c1l1, &c2l2);

            vec4f_t pixel_color = {};

            padd_vec4f(&pixel_color, &c0l0, &c1l1_c2l2);

            pixel_color = abs_vec4f(pixel_color);

            render_target.color_buffer.pixels[x + row_offset] = vec4f_to_color(pixel_color);
            /* 
            if ((int)(floor(pixel_color.x * 8) + floor(pixel_color.y * 8)) % 2 == 0){
              render_target.color_buffer.pixels[x + row_offset] = vec4f_to_color((vec4f_t){1.f, 0.f, 0.f, 1.f});
            }
            else{
              render_target.color_buffer.pixels[x + row_offset] = vec4f_to_color((vec4f_t){1.f, 1.f, 1.f, 1.f});
            }
            */
          }
        }
      }
    }
  }
}
