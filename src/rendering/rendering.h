#ifndef RENDERING_H
#define RENDERING_H

#include "mesh.h"
#include "pixelbuffer.h"
#include "rendercommand.h"

void render_draw_call(pixel_buffer_t *pixel_buff, render_command_t command);

#endif
