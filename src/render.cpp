#include "render.h"

extern std::map<std::string, SDL_Surface*> textures;

void set_pixel(SDL_Surface* surface, int x, int y, SDL_Color color)
{
  if(x < 0 || x >= surface->w || y < 0 || y >= surface->h) return;

  Uint32 * pixel = (Uint32 *) ((Uint8 *) surface->pixels
		  + y * surface->pitch
		  + x * surface->format->BytesPerPixel);
  *pixel = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
}

// FIX: Make gradient proportional to width like render_walls.
// background
// Purpose: Draws the background gradient.
// Parameters:
//   renderer: The renderer to draw with.
// Returns: void
void render_background(SDL_Surface *surface)
{
  for(int y = 0; y < surface->h; y++)
  {
    float v = float(y) / surface->h;

    SDL_Color col;
    if(v < 0.5)
    {
      col = lerp_color(background_colors[1], background_colors[0], v * 2);
    } else {
      col = lerp_color(background_colors[2], background_colors[1], v * 2 - 1);
    }

    for(int x = 0; x < surface->w; x++)
    {
      set_pixel(surface, x, y, col);
    }
  }
}

// render_walls
// Purpose: Renders the walls in from of the player.
// Parameters:
//   renderer: The renderer to draw the walls with.
// Returns: void
void render_walls(SDL_Surface *surface)
{
  vec2 dir = vec2(0, 1).rotate(Player.getRotation());

  for(int i = 0; i < surface->w; i++)
  {
    float u = float(i) / surface->w * 2 - 1;

    vec2 plane = vec2(u * FOV, 0).rotate(Player.getRotation());

    vec2 camdir = dir.add(plane).normalize();

    vec2 end;
    float dist;
    uint8_t wall;
    bool norm;
    if(raycast(Player.getPosition(), camdir, RANGE, end, dist, wall, norm))
    {
      float camdist = end.sub(Player.getPosition()).rotate(-Player.getRotation()).y;

      int height = surface->w / 2 / camdist;
      int gap = (surface->h - height) / 2;

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
	if(gap + j < 0 || gap + j > surface->h) continue;

	uint texY = floor(float(j) / height * texture->h);
	uint texX = int(floor(norm ? end.x * texture->w : end.y * texture->w)) % texture->w;

	Uint8 red;
	Uint8 green;
	Uint8 blue;

	Uint8* pixels;
	pixels = reinterpret_cast<Uint8 *>(texture->pixels) + texY * texture->pitch + texX * texture->format->BytesPerPixel;

	SDL_GetRGB(*reinterpret_cast<Uint32 *>(pixels), texture->format, &red, &green, &blue);

	set_pixel(surface, i, j + gap, {red, green, blue, 255});
      }
    }
  }
}

void screenshot(SDL_Surface *surface)
{
  SDL_SaveBMP(surface, "screenshot.bmp");

  log(log_level::Info, "Took screenshot");
}

void render_profiler(SDL_Surface* surface, double background, double walls, double ui) {
  double total = background + walls + ui;

  float prop_background = background / total;
  float prop_walls = walls / total;
  float prop_ui = ui / total;

  for(int i = 0; i < prop_background * surface->h; i++)
  {
    set_pixel(surface, 0, i, {255, 0, 0, 255});
  }

  for(int i = prop_background * surface->h; i < (prop_background + prop_walls) * surface->h; i++)
  {
    set_pixel(surface, 0, i, {0, 255, 0, 255});
  }

  for(int i = (prop_background + prop_walls) * surface->h; i < surface->h; i++)
  {
    set_pixel(surface, 0, i, {0, 0, 255, 255});
  }
}
