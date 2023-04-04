#include "render.h"

// FIX: Make gradient proportional to width like render_walls.
// background
// Purpose: Draws the background gradient.
// Parameters:
//   renderer: The renderer to draw with.
// Returns: void
void render_background(SDL_Renderer *renderer)
{
  int w, h;
  SDL_RenderGetLogicalSize(renderer, &w, &h);

  for(int y = 0; y < h; y++)
  {
    float v = float(y) / h;

    color col;
    if(v < 0.5)
    {
      col = lerp_color(background_colors[1], background_colors[0], v * 2);
    } else {
      col = lerp_color(background_colors[2], background_colors[1], v * 2 - 1);
    }

    SDL_SetRenderDrawColor(renderer, col.red, col.green, col.blue, col.alpha);
    SDL_RenderDrawLine(renderer, 0, y, w, y);
  }
}

// render_walls
// Purpose: Renders the walls in from of the player.
// Parameters:
//   renderer: The renderer to draw the walls with.
// Returns: void
void render_walls(SDL_Renderer *renderer)
{
  int w, h;
  SDL_RenderGetLogicalSize(renderer, &w, &h);

  vec2 dir = vec2(0, 1).rotate(Player.ang);

  for(int i = 0; i < w; i++)
  {
    float u = float(i) / w * 2 - 1;

    vec2 plane = vec2(u * FOV, 0).rotate(Player.ang);

    vec2 camdir = dir.add(plane).normalize();

    vec2 end;
    float dist;
    uint8_t wall;
    bool norm;
    if(raycast(Player.pos, camdir, RANGE, end, dist, wall, norm))
    {
      float camdist = end.sub(Player.pos).rotate(-Player.ang).y;

      int height = w / 2 / camdist;
      int gap = (h - height) / 2;

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

      if(height > h)
      {
        gap = 0;
        height = h;
      }

      color col = colors[wall - 1].mul(mul);

      SDL_SetRenderDrawColor(renderer, col.red, col.green, col.blue, col.alpha);
      SDL_RenderDrawLine(renderer, i, gap, i, gap + height);
    }
  }
}