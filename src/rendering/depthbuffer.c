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

  db->width = width;
  db->height = height;
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

  free(db->depth_values);
  db->depth_values = NULL;
};

void clear_depth_buffer(depth_buffer_t db, uint32_t value){
  int size = db.width * db.height;  

  for (int i = 0; i < size; i++){
    db.depth_values[i] = value;
  }
}

bool depth_test(depth_test_t mode, uint32_t value, uint32_t ref){
  switch (mode){
    case ALWAYS: return true;
    case NEVER: return false;
    case LESS: return value < ref;
    case LESS_EQUAL: return value <= ref;
    case GREATER: return value > ref;
    case GREATER_EQUAL: return value >= ref;
    case EQUAL: return value == ref;
    case NOT_EQUAL: return value != ref;
  }

  return true;
}
