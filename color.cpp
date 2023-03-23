#include "color.h"

/*
  Function: make_color
  Purpose: Makes color struct into a uint32_t that SDL2 can use.

  Parameters:
    color: Color struct to be converted.
  Returns: Color in uint32_t form.
*/
uint32_t make_color(color color)
{
  return color.blue | (color.green << 8) | (color.red << 16) | (color.alpha << 24);
}