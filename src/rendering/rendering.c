#include "rendering.h"

void render_draw_call(render_target_t render_target, render_command_t command){
  if (!render_target.depth_buffer.depth_values || !render_target.color_buffer.pixels){
    engine_log("RENDERING", "Invalid pointers to pixel data and depth buffer in render_draw_call", ERROR);
  }

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

            //depth test 
            if (render_target.depth_buffer.depth_values){
              float z = l0 * v0.z + l1 * v1.z + l2* v2.z;

              uint32_t depth = (0.5f + 0.5f * z) * UINT32_MAX;

              uint32_t* old_depth_ptr = &render_target.depth_buffer.depth_values[x + y * render_target.depth_buffer.height];
              uint32_t old_depth = *old_depth_ptr;
              if (!depth_test(command.depth.mode, depth, old_depth)) continue;
              if (command.depth.write) *old_depth_ptr = depth;
            }

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

void render_depth_buffer(render_target_t rt){
  float float_max = (float)UINT32_MAX;
  uint32_t vp_width = rt.viewport.xmax - rt.viewport.xmin;
  uint32_t vp_height = rt.viewport.ymax - rt.viewport.ymin;

  uint32_t vp_scale_x = rt.color_buffer.width / vp_width;
  uint32_t vp_scale_y = rt.color_buffer.height / vp_height;

  for (int vp_y = rt.viewport.ymin; vp_y < rt.viewport.ymax; vp_y++){
    uint32_t rel_y = vp_y - rt.viewport.ymin;
    uint32_t cb_y = rel_y * vp_scale_y;
    uint32_t cb_row_offset = rt.color_buffer.height * cb_y;
    uint32_t vp_row_offset = rt.color_buffer.height * vp_y;

    for (int vp_x = rt.viewport.xmin; vp_x < rt.viewport.xmax; vp_x++){
      uint32_t rel_x = vp_x - rt.viewport.xmin;
      uint32_t cb_x = rel_x * vp_scale_x;

      uint32_t value = rt.depth_buffer.depth_values[cb_x + cb_row_offset];
       
      float float_val = (float)value;
      float nrm_red_original = float_val / float_max;
      float nrm_red_scaled = nrm_red_original * 4;
      float nrm_red_clamped = nrm_red_scaled - floor(nrm_red_scaled);
     
      vec4f_t pixel_color = {1.f, nrm_red_clamped, nrm_red_clamped, 1.0f};

      rt.color_buffer.pixels[vp_x + vp_row_offset] = vec4f_to_color(pixel_color);
    }
  }
}

void render_depth_buffer2(render_target_t render_target) {
  const float float_max = (float)UINT32_MAX;

  const uint32_t dst_min_x = render_target.viewport.xmin;
  const uint32_t dst_max_x = render_target.viewport.xmax;
  const uint32_t dst_min_y = render_target.viewport.ymin;
  const uint32_t dst_max_y = render_target.viewport.ymax;
  const uint64_t dst_range_x = (uint64_t)dst_max_x - dst_min_x;
  const uint64_t dst_range_y = (uint64_t)dst_max_y - dst_min_y;

  const uint32_t src_min_x = 0;
  const uint32_t src_max_x = render_target.depth_buffer.width;
  const uint32_t src_min_y = 0;
  const uint32_t src_max_y = render_target.depth_buffer.height;
  const uint64_t src_range_x = (uint64_t)src_max_x - src_min_x;
  const uint64_t src_range_y = (uint64_t)src_max_y - src_min_y;

  const uint32_t buffer_width = render_target.color_buffer.width;
  const uint32_t depth_buffer_width = render_target.depth_buffer.width;

  for (uint32_t y = dst_min_y; y < dst_max_y; y++) {
    
    uint64_t shifted_y = (uint64_t)y - dst_min_y;
    
    uint64_t bias_y = dst_range_y / 2;
    
    uint32_t src_y = (uint32_t)(((shifted_y * src_range_y) + bias_y) / dst_range_y + src_min_y);
    
    uint32_t src_row_offset = src_y * depth_buffer_width;
    uint32_t dst_row_offset = y * buffer_width; 

    for (uint32_t x = dst_min_x; x < dst_max_x; x++) {
      
      uint64_t shifted_x = (uint64_t)x - dst_min_x;
      uint64_t bias_x = dst_range_x / 2;
      uint32_t src_x = (uint32_t)(((shifted_x * src_range_x) + bias_x) / dst_range_x + src_min_x);
      
      uint32_t src_index = src_row_offset + src_x;

      uint32_t dst_index = dst_row_offset + x;
      
      uint32_t depth_val = render_target.depth_buffer.depth_values[src_index];
      if (depth_val == UINT32_MAX){
        render_target.color_buffer.pixels[dst_index] = vec4f_to_color((vec4f_t){0.f, 0.f, 0.f, 1.f});
        continue;
      } 
       
      float float_val = (float)depth_val;
      float nrm_red_original = float_val / float_max;
      float nrm_red_scaled = nrm_red_original * 10;
      float nrm_red_clamped = nrm_red_scaled - floor(nrm_red_scaled);
     
      vec4f_t pixel_color = {1.f, nrm_red_clamped, nrm_red_clamped, 1.0f};

      render_target.color_buffer.pixels[dst_index] = vec4f_to_color(pixel_color);
    }
  }
}
