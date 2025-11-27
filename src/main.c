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

    render_buffer_t rb = {
      .pixels = (color_t*)draw_surface->pixels,
      .width = (uint32_t)width,
      .height = (uint32_t)height,
    };


    vec4f_t color_vec = {ONE_F, 0, 0, ONE_F};
    color_t color = vec4f_to_color(color_vec);
    clear_render_buffer(rb, (color_t)color);

    SDL_Rect rect = {.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}
