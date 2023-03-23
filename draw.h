#ifndef DRAW_H
#define DRAW_H 1

#include <SDL2/SDL.h>

#include "color.h"

void set_pixel(SDL_Surface *surface, int x, int y, struct color pixel);

void draw_vert(SDL_Surface *surface, int x, int y, int length, color color);

#endif