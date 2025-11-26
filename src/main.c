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

  bool running = true;
  while(running){
    SDL_Event event;
    while (SDL_PollEvent(&event)){
      switch (event.type){
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
              running = false;
              break;
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
    
    if (!draw_surface){
      draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
      SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_NONE);
    }

    render_buffer_t rb = {
      .pixels = (color_t*)draw_surface->pixels,
      .width = (uint32_t)width,
      .height = (uint32_t)height,
    };

    clear_render_buffer(rb, (color_t){255, 255, 255, 255});

    SDL_Rect rect = {.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);

    SDL_UpdateWindowSurface(window);
  }

  return 0;
}
