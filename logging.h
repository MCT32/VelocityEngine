#ifndef LOGGING_H
#define LOGGING_H 1

#include <fstream>
#include <cstring>

extern std::ofstream log_file;

void init_log();
void end_log();
void log(char* message);

#endif