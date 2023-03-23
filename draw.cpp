#include "draw.h"

/*
  Function: set_pixel
  Purpose: Draws a pixel to the surface.

  Parameters:
    surface: Surface to draw pixel to.
    x: X coord of pixel.
    y: Y coord of pixel.
    pixel: Color of pixel to draw.
  Returns: Nothing.
*/
void set_pixel(SDL_Surface *surface, int x, int y, struct color pixel)
{
  uint32_t upixel = make_color(pixel);

  uint32_t * const target_pixel = reinterpret_cast<uint32_t *>((uint8_t *) surface->pixels
    + y * surface->pitch
    + x * surface->format->BytesPerPixel);

  *target_pixel = upixel;
}

/*
  Function: draw_vert
  Purpose: Draws a vertical line on the surface.

  Parameters:
    surface: Surface to draw line on.
    x: X coord of starting point.
    y: Y coord of starting point.
    length: Length of the line.
    color: Color of the line.
  Returns: Nothing.
*/
void draw_vert(SDL_Surface *surface, int x, int y, int length, color color)
{
  for(int i = 0; i < length; i++)
  {
    if(x >= 0 && x < surface->w && y + i >= 0 && y + i < surface->h) set_pixel(surface, x, y + i, color);
  }
}