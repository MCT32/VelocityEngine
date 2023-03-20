#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "vec2.h"

#define FOV 1 // Defines the width of the camera plane

#define RANGE 8 // Defines how far rays are allowed to travel to find intersections

#define PI 3.14159

template<typename T>
T lerp(T v1, T v2, float fac)
{
  return v1 * fac + v2 * (1 - fac);
}

// Can be used to create colors used by SDL2
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

color lerp(color v1, color v2, float fac)
{
  return color {lerp(v1.alpha, v2.alpha, fac), lerp(v1.red, v2.red, fac), lerp(v1.green, v2.green, fac), lerp(v1.blue, v2.blue, fac)};
}

// Pre-defined colors of walls in the map
color colors[8];

color background_colors[3];

// Layout of the map
uint8_t *map;
uint8_t mapWidth, mapHeight;

// Defines the player
struct {
  vec2 pos = vec2(3.5, 3.5);
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

// FIX: Make gradient proportional to width like render_walls.
// background
// Purpose: Draws the background gradient.
// Parameters:
//   surface: The surface to draw to.
// Returns: void
void background(SDL_Surface *surface)
{
  for(int y = 0; y < surface->h; y++)
  {
    for(int x = 0; x < surface->w; x++)
    {
      float v = float(y) / surface->h;

      color col;
      if(v < 0.5)
      {
        col = lerp(background_colors[1], background_colors[0], v * 2);
      } else {
        col = lerp(background_colors[2], background_colors[1], v * 2 - 1);
      }

      set_pixel(surface, x, y, col);
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
bool raycast(vec2 start, vec2 dir, float range, vec2 &end, float &dist, uint8_t &wall, bool &normal)
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

      normal = false;
    } else {
      step = dy / dir.y;

      if(dy > 0)
      {
        cellY++;
      } else {
        cellY--;
      }

      normal = true;
    }

    tempdist += step;
    if(abs(tempdist) > range) return false;

    current.x += dir.x * step;
    current.y += dir.y * step;

    if(cellX >= 0 && cellY >= 0 && cellX < mapWidth && cellY < mapHeight)
    {
      if(map[cellX + cellY * mapWidth])
      {
        end = current;
        dist = abs(tempdist);
        wall = map[cellX + cellY * mapWidth];

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
    if(x >= 0 && x < surface->w && y + i >= 0 && y + i < surface->h) set_pixel(surface, x, y + i, color);
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
  vec2 dir = vec2(0, 1).rotate(player.ang);

  for(int i = 0; i < surface->w; i++)
  {
    float u = float(i) / surface->w * 2 - 1;

    vec2 plane = vec2(u * FOV, 0).rotate(player.ang);

    vec2 camdir = dir.add(plane).normalize();

    vec2 end;
    float dist;
    uint8_t wall;
    bool norm;
    if(raycast(player.pos, camdir, RANGE, end, dist, wall, norm))
    {
      float camdist = end.sub(player.pos).rotate(-player.ang).y;

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

void walk(float distance)
{
  vec2 dir = vec2(0, 1).rotate(player.ang);

  vec2 end;
  float dist;
  uint8_t wall;
  bool norm;
  if(!raycast(player.pos, dir, distance, end, dist, wall, norm))
  {
    player.pos = player.pos.add(dir.mul(distance));
  } else {
    if(!norm)
    {
      player.pos.y += dir.y * distance;
    } else {
      player.pos.x += dir.x * distance;
    }
  }
}

color load_color(std::ifstream &file)
{
  char* buffer = new char[4 * sizeof(uint8_t)];
  file.read(&buffer[0], 4 * sizeof(uint8_t));

  return color {buffer[0], buffer[1], buffer[2], buffer[3]}; 
}

float load_float(std::ifstream &file)
{
  float buffer;
  file.read(reinterpret_cast<char*>(&buffer), sizeof(float));

  return buffer;
}

uint8_t load_uint8_t(std::ifstream &file)
{
  uint8_t buffer;
  file.read(reinterpret_cast<char*>(&buffer), sizeof(uint8_t));

  return buffer;
}

void load_map()
{
  std::ifstream mapfile ("map.gm", std::ifstream::binary);

  // Load wall colors
  for(int i = 0; i < 8; i++)
  {
    colors[i] = load_color(mapfile);
  }

  // Load floor, middle and roof colors
  for(int i = 0; i < 3; i++)
  {
    background_colors[i] = load_color(mapfile);
  }

  // Load player position
  player.pos.x = load_float(mapfile);
  player.pos.y = load_float(mapfile);

  mapWidth = load_uint8_t(mapfile);
  mapHeight = load_uint8_t(mapfile);

  map = new uint8_t[mapWidth * mapHeight];

  mapfile.read(reinterpret_cast<char*>(map), mapWidth * mapHeight * sizeof(uint8_t));
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
    680, 480,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );

  if (window == NULL)
  {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }

  load_map();

  SDL_Event event;
  bool quit = false;

  uint64_t NOW = SDL_GetPerformanceCounter();
  uint64_t LAST = 0;
  double deltaTime = 0;

  while (!quit)
  {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency()) / 1000;

    while (SDL_PollEvent(&event))
    {
      switch (event.type) {
        case SDL_QUIT: quit = true; break;
      default:
        break;
      }
    }

    const uint8_t* pKeystate = SDL_GetKeyboardState(NULL);
    if(pKeystate[SDL_SCANCODE_UP])
    {
      walk(deltaTime);
    }
    if(pKeystate[SDL_SCANCODE_DOWN])
    {
      walk(-deltaTime);
    }
    if(pKeystate[SDL_SCANCODE_RIGHT])
    {
      player.ang -= deltaTime * PI;
    }
    if(pKeystate[SDL_SCANCODE_LEFT])
    {
      player.ang += deltaTime * PI;
    }

    surface = SDL_GetWindowSurface(window);

    background(surface);

    render_walls(surface);

    SDL_UpdateWindowSurface(window);

    printf("framerate: %f\n", 1 / deltaTime);
  }
}
