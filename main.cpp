#include <SDL2/SDL.h>
#include <stdio.h>

#include "vec2.h"

// TODO: Allow resizing
// Pre-defined resolution
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define FOV 1 // Defines the width of the camera plane

#define RANGE 8 // Defines how far rays are allowed to travel to find intersections

#define PI 3.14159

// Can be used to create colors used by SDL2
struct color
{
  uint8_t alpha;
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

// Pre-defined colors of walls in the map
color colors[4] = {
  {  0,   0,   0,   0},
  {255, 255,   0,   0}, // Red
  {255,   0, 255,   0}, // Green
  {255,   0,   0, 255}, // Blue
};

// TODO: Load map and other variables from binary file
// Layout of the map
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

// Defines the player
struct {
  vec2 pos = vec2(4, 4);
  float ang = 0;
} player;

// make_color
// Purpose: Converts the color structure to a uint32_t to be used by SDL2
// Parameters:
//   color: The color to make in the form of a struct
// Returns: The color in the type uint32_t
uint32_t make_color(color color)
{
  return color.blue | (color.green << 8) | (color.red << 16) | (color.alpha << 24);
}


// set_pixel
// Purpose: Draws a pixel to a surface.
// Parameters:
//   surface: The surface to draw the pixel to.
//   x: The x-coordinate of the pixel.
//   y: The y-coordinate of the pixel.
//   color: The color to be drawn to the pixel.
// Returns: void
void set_pixel(SDL_Surface *surface, int x, int y, struct color pixel)
{
  uint32_t upixel = make_color(pixel);

  uint32_t * const target_pixel = (uint32_t *) ((uint8_t *) surface->pixels
    + y * surface->pitch
    + x * surface->format->BytesPerPixel);

  *target_pixel = upixel;
}

// TODO: Allow gradient colors to be selected
// background
// Purpose: Draws the background gradient.
// Parameters:
//   surface: The surface to draw to.
// Returns: void
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

// raycast
// Purpose: Shoots a ray fom the origin untill it intersects a wall.
// Parameters:
//   start: The starting point of the ray.
//   dir: The direction for the ray to travel.
//   range: How far the ray is allowed to travel.
//   &end: A reference parameter for the point of intersection.
//   &dist: A reference parameter for the distance the ray has traveled.
//   &wall: The type of wall hit.
// Returns: True id the ray hits a wall, false otherwise.
bool raycast(vec2 start, vec2 dir, float range, vec2 &end, float &dist, uint8_t &wall)
{
  vec2 current = start;

  int cellX = floor(start.x);
  int cellY = floor(start.y);

  float tempdist = 0;

  while(true)
  {
    float dx, dy;

    if(dir.x > 0)
    {
      dx = (cellX + 1) - current.x;
    } else {
      dx = cellX - current.x;
    }

    if(dir.y > 0)
    {
      dy = (cellY + 1) - current.y;
    } else {
      dy = cellY - current.y;
    }

    float step;
    if(abs(dx / dir.x) <= abs(dy / dir.y))
    {
      step = dx / dir.x;

      if(dx > 0)
      {
        cellX++;
      } else {
        cellX--;
      }
    } else {
      step = dy / dir.y;

      if(dy > 0)
      {
        cellY++;
      } else {
        cellY--;
      }
    }

    tempdist += step;
    if(abs(tempdist) > range) return false;

    current.x += dir.x * step;
    current.y += dir.y * step;

    if(cellX >= 0 && cellY >= 0 && cellX < 8 && cellY < 8)
    {
      if(map[cellX][cellY])
      {
        end = current;
        dist = abs(tempdist);
        wall = map[cellX][cellY];

        return true;
      }
    }
  }
}

// draw_vert
// Purpose: Draws a vertical line to the screen.
// Parameters:
//   surface: The surface to draw the line on.
//   x: The x-coordinate of the line.
//   y: The y coordinate of the start of the line.
//   length: The length of the line.
//   color: The color of the line.
// Returns: void
void draw_vert(SDL_Surface *surface, int x, int y, int length, color color)
{
  for(int i = 0; i < length; i++)
  {
    if(x >= 0 && x < SCREEN_WIDTH && y + i >= 0 && y + i < SCREEN_HEIGHT) set_pixel(surface, x, y + i, color);
  }
}

// render_walls
// Purpose: Renders the walls in from of the player.
// Parameters:
//   surface: The surface to draw the walls on.
// Returns: void
void render_walls(SDL_Surface *surface)
{
  vec2 dir = vec2(0, 1).rotate(player.ang);

  for(int i = 0; i < SCREEN_WIDTH; i++)
  {
    float u = float(i) / SCREEN_WIDTH * 2 - 1;

    vec2 plane = vec2(u * FOV, 0).rotate(player.ang);

    vec2 camdir = dir.add(plane).normalize();

    vec2 end;
    float dist;
    uint8_t wall;
    if(raycast(player.pos, camdir, RANGE, end, dist, wall))
    {
      float camdist = end.sub(player.pos).rotate(-player.ang).y;

      int height = SCREEN_HEIGHT/ camdist;
      int gap = (SCREEN_HEIGHT - height) / 2;

      draw_vert(surface, i, gap, height, colors[wall]);
      
    }
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

  uint64_t NOW = SDL_GetPerformanceCounter();
  uint64_t LAST = 0;
  double deltaTime = 0;

  while (!quit)
  {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency() / 1000);

    while (SDL_PollEvent(&event))
    {
      switch (event.type) {
        case SDL_QUIT: quit = true; break;
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_UP)
          {
            player.pos = player.pos.add(vec2(0, deltaTime * 2).rotate(player.ang));
          }
          if(event.key.keysym.sym == SDLK_DOWN)
          {
            player.pos = player.pos.add(vec2(0, -deltaTime * 2).rotate(player.ang));
          }
          if(event.key.keysym.sym == SDLK_LEFT)
          {
            player.ang += deltaTime * PI * 2;
          }
          if(event.key.keysym.sym == SDLK_RIGHT)
          {
            player.ang -= deltaTime * PI * 2;
          }
      default:
        break;
      }
    }

    background(surface);

    render_walls(surface);

    SDL_UpdateWindowSurface(window);
  }
}
