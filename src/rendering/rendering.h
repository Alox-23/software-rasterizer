#ifndef RENDERING_H
#define RENDERING_H

#include <stdbool.h>

#include "mesh.h"
#include "cube.h"
#include "viewport.h"
#include "rendertarget.h"
#include "colorbuffer.h"
#include "depthbuffer.h"
#include "rendercommand.h"

void render_draw_call(render_target_t render_target, render_command_t command);
void render_draw_call2(render_target_t render_target, render_command_t command);
void render_depth_buffer(render_target_t rt);
void render_depth_buffer2(render_target_t render_target);

#endif
