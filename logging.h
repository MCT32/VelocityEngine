#ifndef LOGGING_H
#define LOGGING_H 1

#include <fstream>
#include <cstring>

#include "config.h"

extern std::ofstream log_file;

void init_log();
void end_log();
void log(char* message);

void log_info(char* message);

#endif