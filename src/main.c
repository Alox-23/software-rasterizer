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

    vec4f_t verticies[] = {
      {100.f, 100.f, 0.f, 1.f},
      {200.f, 100.f, 0.f, 1.f},
      {100.f, 200.f, 0.f, 1.f},
    };
    

    for (int i = 0; i < 3; ++i){
      vec4f_t c = {};

      if ((i % 3) == 0) c.x = 1.f;
      if ((i % 3) == 1) c.y = 1.f;
      if ((i % 3) == 2) c.z = 1.f;
      c.w = 0.f;

      render_command_t cmd = {
        .mesh = {
          .positions = verticies,
          .vertex_count = 3,
          .color = c,
        },
        .cull_mode = NONE,
        .transform = {
          {
            {1.f, 0.f, 0.f, i},
            {0.f, 1.f, 0.f, i},
            {0.f, 0.f, 1.f, 0.f},
            {0.f, 0.f, 0.f, 1.f}
          },
        },
      };
      render_draw_call(&rb, cmd);
    }

    SDL_Rect rect = {.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}
