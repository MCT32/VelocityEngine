// Include external headers
#include <SDL2/SDL.h>
#include <stdio.h>

// Include custom headers
#include "vec2.h"
#include "color.h"
#include "draw.h"
#include "util.h"
#include "render.h"
#include "player.h"
#include "load.h"
#include "logging.h"
#include "config.h"

// Global player struct
player Player;

// Wall colors
color colors[8];

// Backgound colors
color background_colors[3];

// Layout of the map
uint8_t *map;
uint8_t mapWidth, mapHeight;

/*
  Function: walk
  Purpose: Moves the player forward by a distance, testing for collisions.

  Parameters:
    distance: Distance the player should move.
  Returns: Nothing.

  TODO: Use box collisions.
*/
void walk(float distance)
{
  vec2 dir = vec2(0, 1).rotate(Player.ang);

  vec2 end;
  float dist;
  uint8_t wall;
  bool norm;
  if(!raycast(Player.pos, dir, distance, end, dist, wall, norm))
  {
    Player.pos = Player.pos.add(dir.mul(distance));
  } else {
    if(!norm)
    {
      Player.pos.y += dir.y * distance;
    } else {
      Player.pos.x += dir.x * distance;
    }
  }
}

/*
  Function: main
  Purpose: Sets up windows and global variables and starts the game loop.

  Parameters:
    argc: Number of arguments.
    argv: Array of arguments.
  Returns: Exit code.
*/
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

  init_log();
  log("TEST");

  SDL_Event event;
  bool quit = false;

  uint64_t NOW = SDL_GetPerformanceCounter();

  while (!quit)
  {
    uint64_t LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    double deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency()) / 1000;

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
      Player.ang -= deltaTime * PI;
    }
    if(pKeystate[SDL_SCANCODE_LEFT])
    {
      Player.ang += deltaTime * PI;
    }

    surface = SDL_GetWindowSurface(window);

    render_background(surface);

    render_walls(surface);

    SDL_UpdateWindowSurface(window);
  }

  end_log();
}
