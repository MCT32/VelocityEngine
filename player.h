#ifndef PLAYER_H
#define PLAYER_H 1

#include <stdint.h>
#include <SDL2/SDL.h>

#include "entity.h"
#include "vec2.h"
#include "util.h"'
#include "config.h"

// Defines the player
class player : public entity
{
  using entity::entity;

public:
  void processInput(const uint8_t* pKeystate, float deltaTime, int relX);
  void accelerate(vec2 wishdir, float deltaTime);
  void friction(float deltaTime);
};

#endif
