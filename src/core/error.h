#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define ANSI_COLOR_RED     "\e[0;31m"
#define ANSI_COLOR_GREEN   "\e[0;32m"
#define ANSI_COLOR_YELLOW  "\e[0;33m"
#define ANSI_COLOR_BLUE    "\e[0;34m"
#define ANSI_COLOR_RESET   "\e[;0m"

typedef enum{
  WARN,
  ERROR,
  INFO,
} error_level_t;

void engine_log(char* section, char* content, error_level_t level);

#endif
