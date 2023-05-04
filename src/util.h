#ifndef UTIL_H
#define UTIL_H 1

#include "color.h"
#include "vec2.h"
#include "player.h"

extern uint8_t mapWidth, mapHeight;
extern uint8_t *map;

template<typename T>
T lerp(T v1, T v2, float fac);

color lerp_color(color v1, color v2, float fac);

float clip(float value, float lower, float upper);

bool raycast(vec2 start, vec2 dir, float range, vec2 &end, float &dist, uint8_t &wall, bool &normal);

#endif // UTIL_H
