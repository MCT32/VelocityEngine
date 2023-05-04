#ifndef LOGGING_H
#define LOGGING_H 1

#include <fstream>
#include <cstring>
#include <iostream>
#include <stdarg.h>

#include "config.h"

enum class log_level : char
{
  Info = 'I',
  Warning = 'W',
  Error = 'E'
};

extern std::ofstream log_file;

void init_log();
void end_log();
void log(log_level const level, std::string_view const message);

#endif
