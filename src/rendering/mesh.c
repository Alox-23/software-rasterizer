#include "mesh.h"

mesh_t* load_mesh_from_file(const char* filename, vec4f_t color, mat4f_t transform) {
    mesh_t* mesh = calloc(1, sizeof(mesh_t));
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        engine_log("MESH", "Could not open file", ERROR);
        free(mesh);
        return NULL;
    }
    
    // First pass: count elements
    char line[256];
    int vertex_count = 0;
    int index_count = 0; // Total indices needed (3 per triangle)
    
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            vertex_count++;
        }
        else if (line[0] == 'f') {
            // Quick count of vertices in face
            int vertices_in_face = 0;
            for (char* p = line + 2; *p; p++) {
                if (*p == ' ') vertices_in_face++;
            }
            vertices_in_face++; // Last vertex
            
            // Convert to triangles: (n-2) triangles * 3 indices
            if (vertices_in_face >= 3) {
                index_count += (vertices_in_face - 2) * 3;
            }
        }
    }
    
    rewind(file);
    
    // Allocate memory
    mesh->positions = calloc(vertex_count, sizeof(vec4f_t));
    mesh->colors = calloc(vertex_count, sizeof(vec4f_t));
    mesh->indices = calloc(index_count, sizeof(uint32_t));
    mesh->count = vertex_count;
    
    // Parse vertices
    vec4f_t* positions = mesh->positions;
    int v_idx = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            float x, y, z;
            if (sscanf(line, "v %f %f %f", &x, &y, &z) == 3) {
                positions[v_idx++] = mul_matvec4f(transform, (vec4f_t){x, y, z, 1.0f});
            }
        }
    }
    
    rewind(file); // Rewind to parse faces
    
    // Parse faces and generate indices
    uint32_t* indices = mesh->indices;
    int idx_idx = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'f') {
            // Extract vertex indices
            int face_vertices[64];
            int face_count = 0;
            
            char* token = strtok(line + 2, " \n");
            while (token && face_count < 64) {
                // Extract just the vertex index (before any '/')
                int v;
                if (sscanf(token, "%d", &v) == 1) {
                    // Convert to 0-based
                    if (v > 0) v--;
                    else if (v < 0) v = vertex_count + v;
                    
                    if (v >= 0 && v < vertex_count) {
                        face_vertices[face_count++] = v;
                    }
                }
                token = strtok(NULL, " \n");
            }
            
            // Triangulate (triangle fan)
            if (face_count >= 3) {
                int v0 = face_vertices[0];
                for (int i = 1; i < face_count - 1; i++) {
                    indices[idx_idx++] = v0;
                    indices[idx_idx++] = face_vertices[i];
                    indices[idx_idx++] = face_vertices[i + 1];
                }
            }
        }
    }
    
    fclose(file);
    
    // Set index count
    mesh->count = idx_idx;
    
    // Apply color to all vertices
    vec4f_t temp_vec = (vec4f_t){0.f, 0.f, 0.f, 0.f};
    if (color.x == temp_vec.x && color.y == temp_vec.x && color.z == temp_vec.z && color.w == temp_vec.w){
      for (int i = 0; i < vertex_count; i++) {
          mesh->colors[i] = make_random_vec4f();
      }
    }
    else{
      for (int i = 0; i < vertex_count; i++) {
        mesh->colors[i] = color;
      }
    }
    
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
