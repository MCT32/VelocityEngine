#include "render.h"

extern std::map<std::string, SDL_Surface*> textures;

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

    SDL_Color col;
    if(v < 0.5)
    {
      col = lerp_color(background_colors[1], background_colors[0], v * 2);
    } else {
      col = lerp_color(background_colors[2], background_colors[1], v * 2 - 1);
    }

    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.b, col.a);
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

  vec2 dir = vec2(0, 1).rotate(Player.getRotation());

  for(int i = 0; i < w; i++)
  {
    float u = float(i) / w * 2 - 1;

    vec2 plane = vec2(u * FOV, 0).rotate(Player.getRotation());

    vec2 camdir = dir.add(plane).normalize();

    vec2 end;
    float dist;
    uint8_t wall;
    bool norm;
    if(raycast(Player.getPosition(), camdir, RANGE, end, dist, wall, norm))
    {
      float camdist = end.sub(Player.getPosition()).rotate(-Player.getRotation()).y;

      int height = w / 2 / camdist;
      int gap = (h - height) / 2;

      SDL_Surface* texture = textures[wall_textures[wall-1]];

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

      for(int j = 0; j < height; j++)
      {
	if(gap + j < 0 || gap + j > h) continue;

	uint texY = floor(float(j) / height * texture->h);
	uint texX = int(floor(norm ? end.x * texture->w : end.y * texture->w)) % texture->w;

	Uint8 red;
	Uint8 green;
	Uint8 blue;

	Uint8* pixels;
	pixels = reinterpret_cast<Uint8 *>(texture->pixels) + texY * texture->pitch + texX * texture->format->BytesPerPixel;

	SDL_GetRGB(*reinterpret_cast<Uint32 *>(pixels), texture->format, &red, &green, &blue);

        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
	SDL_RenderDrawPoint(renderer, i, j + gap);
      }
    }
  }
}

void screenshot(SDL_Renderer *renderer)
{
  const Uint32 format = SDL_PIXELFORMAT_ARGB8888;
  int w, h;
  SDL_GetRendererOutputSize(renderer, &w, &h);

  SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format);
  if(!surface)
  {
    log(log_level::Error, "Could not create surface for screenchot: " + std::string(SDL_GetError()));
    return;
  }
  if(SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch))
  {
    log(log_level::Error, "Could not read pixels from renderer: " + std::string(SDL_GetError()));
    return;
  }
  SDL_SaveBMP(surface, "screenshot.bmp");
  SDL_FreeSurface(surface);

  log(log_level::Info, "Took screenshot");
}
