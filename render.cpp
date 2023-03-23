#include "render.h"

// FIX: Make gradient proportional to width like render_walls.
// background
// Purpose: Draws the background gradient.
// Parameters:
//   surface: The surface to draw to.
// Returns: void
void render_background(SDL_Surface *surface)
{
  for(int y = 0; y < surface->h; y++)
  {
    for(int x = 0; x < surface->w; x++)
    {
      float v = float(y) / surface->h;

      color col;
      if(v < 0.5)
      {
        col = lerp_color(background_colors[1], background_colors[0], v * 2);
      } else {
        col = lerp_color(background_colors[2], background_colors[1], v * 2 - 1);
      }

      set_pixel(surface, x, y, col);
    }
  }
}

// FIX: Artifacts on first render.
// render_walls
// Purpose: Renders the walls in from of the player.
// Parameters:
//   surface: The surface to draw the walls on.
// Returns: void
void render_walls(SDL_Surface *surface)
{
  vec2 dir = vec2(0, 1).rotate(Player.ang);

  for(int i = 0; i < surface->w; i++)
  {
    float u = float(i) / surface->w * 2 - 1;

    vec2 plane = vec2(u * FOV, 0).rotate(Player.ang);

    vec2 camdir = dir.add(plane).normalize();

    vec2 end;
    float dist;
    uint8_t wall;
    bool norm;
    if(raycast(Player.pos, camdir, RANGE, end, dist, wall, norm))
    {
      float camdist = end.sub(Player.pos).rotate(-Player.ang).y;

      int height = surface->w / 2 / camdist;
      int gap = (surface->h - height) / 2;

      float mul;
      if(norm)
      {
        mul = 0.8 - (camdist / RANGE);
      } else {
        mul = 1 - (camdist / RANGE);
      }

      if(mul < 0)
      {
        mul = 0;
      }
      if(mul > 1)
      {
        mul = 1;
      }

      if(height > surface->h)
      {
        gap = 0;
        height = surface->h;
      }

      draw_vert(surface, i, gap, height, colors[wall - 1].mul(mul));
    }
  }
}