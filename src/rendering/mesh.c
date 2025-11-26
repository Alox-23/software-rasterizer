#include "mesh.h"

mesh_t make_mesh(){
  return (mesh_t){
    NULL, //positions
    0, //vertex_count
    {255, 0, 0, 255} //color 
  };
}
