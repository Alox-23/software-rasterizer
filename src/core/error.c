#include <stdio.h>
#include "error.h"

void engine_log(char* section, char* content, error_level_t level){
  switch (level){
    case INFO:
      printf(ANSI_COLOR_GREEN);
      break;
    case WARN:
      printf(ANSI_COLOR_YELLOW);
      break;
    case ERROR:
      printf(ANSI_COLOR_RED);
      break;
  }
  
  printf("%s: %s\n", section, content);
  printf(ANSI_COLOR_RESET);
}
