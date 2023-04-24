#ifndef LOAD_H
#define LOAD_H 1

#include <iostream>
#include <fstream>

#include "color.h"
#include "player.h"
#include "logging.h"

extern player Player;

extern color colors[];
extern color background_colors[];

extern uint8_t mapWidth, mapHeight;
extern uint8_t *map;

color load_color(std::ifstream &file);
float load_float(std::ifstream &file);
uint8_t load_uint8_t(std::ifstream &file);

bool load_map(const char* mapName);

#endif
