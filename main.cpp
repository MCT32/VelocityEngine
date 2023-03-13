#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FOV 1

#define PI 3.14159

struct color
{
  uint8_t alpha;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

color colors[4] = {
  {0, 0, 0, 0},
  {255, 255, 0, 0},
  {255, 0, 255, 0},
  {255, 0, 0, 255},
};

uint8_t map[8][8] = {
  {1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,1},
  {1,0,2,0,2,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,2,0,2,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1},
};

struct {
  float posx = 1.5;
  float posy = 1.5;
  float ang = 0;
} player;

float raycast(float posx, float posy, float dirx, float diry)
{
  int cellx = ceil(posx);
  int celly = ceil(posy);

  float dx, dy;

  float total_dist = 0;

  while(true)
  {
    if(dirx < 0)
    {
     dx = cellx - posx;
    } else {
      dx = posx - cellx;
    }

    if(diry < 0)
    {
      dy = celly - posy;
    } else {
      dy = posy - celly;
    }

    if(abs(dx) < abs(dy))
    {
      float dist = dx / dirx;
      total_dist += abs(dist);

      posx += dx;
      posy += dy;

      if(dx < 0)
      {
        cellx -= 1;
      } else {
        cellx += 1;
      }
    } else {
      float dist = dy / diry;
      total_dist += abs(dist);

      posx += dx;
      posy += dy;

      if(dy < 0)
      {
        celly -= 1;
      } else {
        celly += 1;
      }
    }

    if (map[cellx][celly])
      return total_dist;
  }
}

uint32_t make_color(color color)
{
  return color.blue | (color.green << 8) | (color.red << 16) | (color.alpha << 24);
}

void set_pixel(SDL_Surface *surface, int x, int y, struct color pixel)
{
  uint32_t upixel = make_color(pixel);

  uint32_t * const target_pixel = (uint32_t *) ((uint8_t *) surface->pixels
    + y * surface->pitch
    + x * surface->format->BytesPerPixel);

  *target_pixel = upixel;
}

void background(SDL_Surface *surface)
{
  for(int y = 0; y < SCREEN_HEIGHT; y++)
  {
    for(int x = 0; x < SCREEN_WIDTH; x++)
    {
      float value = 1 - (float(y) / SCREEN_HEIGHT * 2);

      if(value < 0)
        value = 1 - value;

      set_pixel(surface, x, y, color {255, uint8_t(255 * value), uint8_t(255 * value), uint8_t(255 * value)});
    }
  }
}

void draw_vert(SDL_Surface *surface, int x, int y, int length, color color)
{
  for(int i = 0; i < length; i++)
  {
    set_pixel(surface, x, y + i, color);
  }
}

void render_walls(SDL_Surface *surface)
{
  for(int i = 0; i < SCREEN_WIDTH; i++)
  {
    float u = i / SCREEN_WIDTH * 2 - 1;

    float planex = FOV * u * sin(player.ang + PI / 2);
    float planey = FOV * u * cos(player.ang + PI / 2);

    float dirx = sin(player.ang) + planex;
    float diry = cos(player.ang) + planey;

    float dist = raycast(player.posx, player.posy, dirx, diry);

    printf("raycast distance: %f\n", dist);

    draw_vert(surface, i, SCREEN_HEIGHT / 2 * (dist / 20), SCREEN_HEIGHT / 2 * (1 / (dist / 20)), color {255, 255, 0, 0});
  }
}

int main(int argc, char* argv[])
{
  SDL_Window* window = NULL;
  SDL_Surface* surface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  window = SDL_CreateWindow(
    "COOM",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if (window == NULL)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  surface = SDL_GetWindowSurface(window);

  SDL_Event event;
  bool quit = false;

  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type) {
        case SDL_QUIT: quit = true; break;
      default:
        break;
      }
    }

    background(surface);

    render_walls(surface);

    SDL_UpdateWindowSurface(window);
  }
}
