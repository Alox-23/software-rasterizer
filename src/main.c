#include <SDL2/SDL.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "utils/utils.h"
#include "rendering/rendering.h"
#include "core/core.h"

int main(){
  SDL_Init(SDL_INIT_VIDEO);

  int width = 500;
  int height = 500;

  SDL_Window *window = SDL_CreateWindow("Alexander Kuznetsov's Software Rasterizer!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  SDL_Surface *draw_surface = NULL;
  depth_buffer_t db = alloc_depth_buffer(width, height);

  Uint32 last_time = SDL_GetTicks();
  Uint32 last_frame_time = SDL_GetTicks();
  int frame_count = 0;
  float current_fps = 0.f;
  float delta_time;

  int mouse_x = 0;
  int mouse_y = 0;

  float pdx;
  float pdz = 50.f;
  float pdy;
  float speed = 50;
  float rot = 0;
  float yrot = 0;
  float rspeed = 3;
  
  float angle = 1;
  
  mesh_t* castle_mesh = load_mesh_from_file("assets/models/castle_test.obj", (vec4f_t){0.f, 0.f, 0.f, 0.f});
  mesh_t* human_mesh = load_mesh_from_file("assets/models/human_test.obj", (vec4f_t){1.f, 0.f, 0.f, 1.f});
  
  bool running = true;
  while(running){
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_DOWN]) yrot -= rspeed * delta_time;
    if (state[SDL_SCANCODE_UP]) yrot += rspeed * delta_time;
    if (state[SDL_SCANCODE_LEFT]) rot -= rspeed * delta_time;
    if (state[SDL_SCANCODE_RIGHT]) rot += rspeed * delta_time;
    if (state[SDL_SCANCODE_W]) pdz += speed * delta_time;
    if (state[SDL_SCANCODE_S]) pdz -= speed * delta_time;
    if (state[SDL_SCANCODE_A]) pdx += speed * delta_time;
    if (state[SDL_SCANCODE_D]) pdx -= speed * delta_time;
    if (state[SDL_SCANCODE_R]) pdy -= speed * delta_time;
    if (state[SDL_SCANCODE_F]) pdy += speed * delta_time;

    SDL_Event event;
    while (SDL_PollEvent(&event)){
      if (event.type == SDL_QUIT){
        running = false;
        break;
      }
      if (event.type == SDL_KEYDOWN){
        if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = false;
      }
      if (event.type == SDL_WINDOWEVENT){
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED:
            if (draw_surface) SDL_FreeSurface(draw_surface);
            draw_surface = NULL;
            width = event.window.data1;
            height = event.window.data2;

            free_depth_buffer(db);
            db = alloc_depth_buffer(width, height);
            
            break;
        }
      }
      if (event.type == SDL_MOUSEMOTION){
        mouse_y = event.motion.y;
        mouse_x = event.motion.x;
      }
    }

    if (!draw_surface){
      draw_surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
      SDL_SetSurfaceBlendMode(draw_surface, SDL_BLENDMODE_NONE);
    }
 
    color_buffer_t cb = {
      .pixels = (color_t*)draw_surface->pixels,
      .width = (uint32_t)width,
      .height = (uint32_t)height,
    };

    frame_count++;
    Uint32 current_time = SDL_GetTicks();
    delta_time = (float)(current_time - last_time) / 1000.f;
    last_time = current_time;

    if (current_time - last_frame_time >= 1000){
      current_fps = (float)frame_count / ((current_time - last_frame_time) / 1000.f);
      
      char fps_str[50];

      int number_idfk = sprintf(fps_str, "%.2f", current_fps);

      engine_log("FPS", fps_str, INFO);

      frame_count = 0;
      last_frame_time = current_time;
    }
       
    render_target_t rt = {
      .color_buffer = cb,
      .depth_buffer = db,
      .viewport = {
        .xmin = 0,
        .ymin = 0,
        .xmax = (int32_t)cb.width,
        .ymax = (int32_t)cb.height,
      },
    };

    render_target_t depth_buffer_render_output = {
      .color_buffer = cb,
      .depth_buffer = db,
      .viewport = {
        0,
        0,
        100,
        100,
      },
    };

    clear_color_buffer(cb, (vec4f_t){0.718f, 0.435f, 0.788f, 1.f});
    clear_depth_buffer(db, UINT32_MAX);
    
    angle += 0.5 * delta_time;

    mat4f_t perspective = make_perspective_mat4f(0.5f, 1000.f, M_PI / 3.f, width * 1.f / height);
    mat4f_t translate = make_translation_mat4f((vec4f_t){0.f, -10.f, -pdz, 0.f});
    mat4f_t rotation_zx = make_rotationZX_mat4f(angle);
    mat4f_t rotation_zy = make_rotationYZ_mat4f(yrot);
    mat4f_t rotation = mul_mat4f(rotation_zy, rotation_zx);
    mat4f_t castle_final = mul_mat4f(perspective, mul_mat4f(translate, rotation));
    mat4f_t human_final = mul_mat4f(perspective, mul_mat4f(translate, rotation));
   
    render_draw_call(
      rt,
      (render_command_t){
        .mesh = human_mesh,
        .cull_mode = CW,
        .depth = {
          .write = true,
          .mode = LESS,
        },
        .transform = human_final,
      }
    );
    
    render_draw_call(
      rt,
      (render_command_t){
        .mesh = castle_mesh,
        .cull_mode = CW,
        .depth = {
          .write = true,
          .mode = LESS,
        },
        .transform = castle_final,
      }
    );

    //render_depth_buffer(depth_buffer_render_output);

    SDL_Rect rect = {.x = 0, .y = 0, .w = width, .h = height};
    SDL_BlitSurface(draw_surface, &rect, SDL_GetWindowSurface(window), &rect);

    SDL_UpdateWindowSurface(window);
  }

  SDL_FreeSurface(draw_surface);
  free_depth_buffer(db);
  free_mesh(castle_mesh);
  free_mesh(human_mesh);

  return 0;
}
