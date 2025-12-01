#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "utils/utils.h"
#include "rendering/rendering.h"

int main(){
  SDL_Init(SDL_INIT_VIDEO);

  int width = 800;
  int height = 600;

  SDL_Window *window = SDL_CreateWindow("Alexander Kuznetsov's Software Rasterizer!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  SDL_Surface *draw_surface = NULL;

  const Uint64 perf_freq = SDL_GetPerformanceFrequency();
  Uint64 last_time = SDL_GetPerformanceCounter();
  int frame_count = 0;
  float current_fps = 0.f;

  int mouse_x = 0;
  int mouse_y = 0;
  
  float angle = 1;

  bool running = true;
  while(running){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
      switch (event.type){
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
            running = false;
          }
          break;
        case SDL_WINDOWEVENT:
          switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
              if (draw_surface) SDL_FreeSurface(draw_surface);
              draw_surface = NULL;
              width = event.window.data1;
              height = event.window.data2;
              break;
          }
        case SDL_MOUSEMOTION:          
          mouse_y = event.motion.y;
          mouse_x = event.motion.x;
          break;
      }
    }

    frame_count++;
    Uint64 current_time = SDL_GetPerformanceCounter();
    Uint64 elapsed_ticks = current_time - last_time;

    if (elapsed_ticks >= perf_freq){
      current_fps = (float)frame_count / ((float)elapsed_ticks / perf_freq);
 
      printf("FPS: %.2f\n", current_fps);

      last_time = current_time;
      frame_count = 0;
    }

    if (!draw_surface){
      draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
      SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_NONE);
    }

    pixel_buffer_t rb = {
      .pixels = (color_t*)draw_surface->pixels,
      .width = (uint32_t)width,
      .height = (uint32_t)height,
    };

    vec4f_t color_vec = {0.718f, 0.435f, 0.788f, 1.f};
    color_t color = vec4f_to_color(color_vec);
    clear_pixel_buffer(rb, color);

    int trig_size = 50.f;
    int num_trig = 100;
    int row_size = (int)sqrt(num_trig);

    vec4f_t verticies[] = {
      {0.f, 0.f, 0.f, 1.f},
      {0.f, trig_size, 0.f, 1.f},
      {trig_size, 0.f, 0.f, 1.f},
    };

    vec4f_t colors[] = {
      {1.f, 0.f, 0.f, 1.f},
      {0.f, 1.f, 0.f, 1.f},
      {0.f, 0.f, 1.f, 1.f},
    };

    angle += 0.02;
    
    for (int i = 0; i < num_trig; ++i){
      vec4f_t c = {};

      if ((i % 3) == 0) c.x = 1.f;
      if ((i % 3) == 1) c.y = 1.f;
      if ((i % 3) == 2) c.z = 1.f;
      c.w = 0.f;
     
      mat4f_t translation_matrix = make_translation_mat4f(trig_size * (i % row_size) - (row_size * trig_size / 2), trig_size * (i / row_size) - (row_size * trig_size / 2), 0.f);

      mat4f_t rotation_matrix = make_rotation_mat4f(angle);

      mat4f_t final_matrix = mul_mat4f(make_translation_mat4f(mouse_x, mouse_y, 0), mul_mat4f(rotation_matrix, translation_matrix));
      
      render_command_t cmd = {
        .mesh = {
          .positions = verticies,
          .colors = colors,
          .vertex_count = 3,
        },
        .cull_mode = NONE,
        .transform = final_matrix,
      };
      render_draw_call(&rb, cmd);
    }

    SDL_Rect rect = {.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}
