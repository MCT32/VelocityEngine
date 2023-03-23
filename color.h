#ifndef COLOR_H
#define COLOR_H 1

#include <stdint.h>

// Can be used to create colors used by SDL2
// TODO: Impliment basic operators like addition and multiplication.
struct color
{
  uint8_t alpha;
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  color mul(float value)
  {
    return color {alpha, red * value, green * value, blue * value};
  }
};

uint32_t make_color(color color);

#endif