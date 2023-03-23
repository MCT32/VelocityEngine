#ifndef LOAD_H
#define LOAD_H 1

#include <iostream>
#include <fstream>

#include "color.h"
#include "globals.h"


color load_color(std::ifstream &file);
float load_float(std::ifstream &file);
uint8_t load_uint8_t(std::ifstream &file);

void load_map();

#endif