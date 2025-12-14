#include "depthbuffer.h"

void alloc_depth_buffer(depth_buffer_t* db, uint32_t width, uint32_t height){
  if (width < 0 || height < 0){
    engine_log("DEPTH_BUFFER", "invalid size during allocation", ERROR);
    return;
  }

  db->depth_values = calloc(width * height, sizeof(uint32_t));
  if (!db->depth_values){
    engine_log("DEPTH_BUFFER", "Alocation of db->depth_values failed", ERROR);
    return;
  }
}

void free_depth_buffer(depth_buffer_t* db){
  if (!db){
    engine_log("DEPTH_BUFFER", "Invalid db pointer during free_depth_buffer()", ERROR);
    return;
  }
  
  if (!db->depth_values){
    engine_log("DEPTH_BUFFER", "Attempted to free, but not allocated", ERROR);
    return;
  }
};
