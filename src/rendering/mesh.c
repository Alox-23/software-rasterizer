#include "mesh.h"

mesh_t* load_mesh_from_file(const char* filename, vec4f_t color){
  mesh_t* mesh = calloc(1, sizeof(mesh_t));

  FILE* file = fopen(filename, "r");
  if (!file){
    engine_log("MESH", "Could not open file", ERROR);
    return NULL;
  }

  //counting elements
  char line[256];
  int vertex_count = 0, face_count = 0;
  while (fgets(line, sizeof(line), file)){
    if (line[0] == 'v'){
      if (line[1] == ' ') vertex_count++;
    }
    else if (line[0] == 'f'){
      face_count++;
    }
  }
  rewind(file);

  //alocating memory to store mesh attributes
  mesh->positions = calloc(vertex_count, sizeof(vec4f_t));
  mesh->colors = calloc(vertex_count, sizeof(vec4f_t));
  mesh->indices = calloc(face_count * 3, sizeof(uint32_t));
  mesh->count = vertex_count;
 
  //parsing the data
  int vertex_i = 0;
  int index_i = 0;
  while(fgets(line, sizeof(line), file)){
    //skip useless stuf for now
    if (line[0] == '#' || line[0] == '\n'){
      continue;
    }
    //case vertex
    if (line[0] == 'v' && line[1] == ' '){
      float x, y, z;
      sscanf(line, "v %f %f %f", &x, &y, &z);
      mesh->positions[vertex_i] = (vec4f_t){x, y, z, 1.f};
      mesh->colors[vertex_i] = color;
      vertex_i++;
    }
    //case face
    else if (line[0] == 'f'){
      int v1, v2, v3; 
      if (sscanf(line, "f %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &v1, &v2, &v3) == 3 ||
          sscanf(line, "f %d//%*d %d//%*d %d//%*d", &v1, &v2, &v3) == 3 ||
          sscanf(line, "f %d %d %d", &v1, &v2, &v3) == 3){
        //OBJ indices are 1 based so -1 to convert to C-style indexing
        mesh->indices[index_i++] = v1 - 1;
        mesh->indices[index_i++] = v2 - 1;
        mesh->indices[index_i++] = v3 - 1;
      }
    }
  }

  fclose(file);
  
  return mesh;
}

void free_mesh(mesh_t* mesh){
  if (!mesh || !mesh->positions || !mesh->colors || !mesh->indices){
    engine_log("MESH", "Invalid mesh pointer during free_mesh", ERROR);
    return;
  }
  
  free(mesh->positions);
  free(mesh->colors);
  free(mesh->indices);
  free(mesh);
}
