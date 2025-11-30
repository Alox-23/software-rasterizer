#include "../utils/utils.h"

int main (){
  mat4f_t matrix = {
    {
      {1.f, 0.f, 0.f, 2.f},
      {0.f, 1.f, 0.f, 2.f},
      {0.f, 0.f, 1.f, 1.f},
      {0.f, 0.f, 0.f, 1.f}
    },
  };

  vec4f_t v0 = {2.f, 2.f, 1.f, 1.f};
  vec4f_t r0 = mul_matvec4f(matrix, v0);

  print_vec4f("v0", v0);
  print_vec4f("r0", r0);

  return 0;
}
