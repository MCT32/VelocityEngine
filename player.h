#ifndef PLAYER_H
#define PLAYER_H 1

#include <stdint.h>

#include "vec2.h"
#include "util.h"

// Defines the player
struct player
{
  vec2 pos = vec2(3.5, 3.5);
  float ang = 0;

  float size = 0.5;
};

#endif
