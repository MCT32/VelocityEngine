#ifndef LOAD_H
#define LOAD_H 1

#include <iostream>
#include <fstream>
#include <SDL2/SDL_image.h>
#include <string>

#include "player.h"
#include "logging.h"

extern player Player;

extern SDL_Color background_colors[];

extern uint8_t mapWidth, mapHeight;
extern uint8_t *map;

SDL_Color load_color(std::ifstream &file);
float load_float(std::ifstream &file);
uint8_t load_uint8_t(std::ifstream &file);
void load_texture(std::string name);

bool load_map(std::string mapName);

#endif
