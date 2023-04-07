#ifndef PLAYER_H
#define PLAYER_H 1

#include <stdint.h>

#include "entity.h"
#include "vec2.h"
#include "util.h"

// Defines the player
class player : public entity
{
  using entity::entity;
};

#endif
