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
*/
void walk(vec2 deltaPos)
{
  vec2 newPos = Player.pos.add(deltaPos);
  int x = floor(Player.pos.x);
  int y = floor(Player.pos.y);

  // +x
  if(x < mapWidth - 1 && map[x + 1 + y * mapWidth])
  {
    if(newPos.x + Player.size / 2 > x + 1)
    {
      newPos.x = x + 1 - Player.size / 2;
    }
  }

  // -x
  if(x > 0 && map[x - 1 + y * mapWidth])
  {
    if(newPos.x - Player.size / 2 < x)
    {
      newPos.x = x + Player.size / 2;
    }
  }

  // +y
  if(y < mapHeight - 1 && map[x + (y + 1) * mapWidth])
  {
    if(newPos.y + Player.size / 2 > y + 1)
    {
      newPos.y = y + 1 - Player.size / 2;
    }
  }

  // -y
  if(y > 0 && map[x + (y - 1) * mapWidth])
  {
    if(newPos.y - Player.size / 2 < y)
    {
      newPos.y = y + Player.size / 2;
    }
  }

  // +x +y
  if(x < mapWidth - 1 && y < mapHeight - 1 && map[x + 1 + (y + 1) * mapWidth])
  {
    if(x + 1 - newPos.x >= y + 1 - newPos.y)
    {
      if(newPos.x + Player.size / 2 > x + 1)
      {
        newPos.x = x + 1 - Player.size / 2;
      }
    } else {
      if(newPos.y + Player.size / 2 > y + 1)
      {
        newPos.y = y + 1 - Player.size / 2;
      }
    }
  }

  // -x +y
  if(x > 0 - 1 && y < mapHeight - 1 && map[x - 1 + (y + 1) * mapWidth])
  {
    if(newPos.x - x >= y + 1 - newPos.y)
    {
      if(newPos.x - Player.size / 2 < x)
      {
        newPos.x = x + Player.size / 2;
      }
    } else {
      if(newPos.y + Player.size / 2 > y + 1)
      {
        newPos.y = y + 1 - Player.size / 2;
      }
    }
  }

  // +x -y
  if(x < mapWidth - 1 && y > 0 && map[x + 1 + (y - 1) * mapWidth])
  {
    if(x + 1 - newPos.x >= newPos.y - y)
    {
      if(newPos.x + Player.size / 2 > x + 1)
      {
        newPos.x = x + 1 - Player.size / 2;
      }
    } else {
      if(newPos.y - Player.size / 2 < y)
      {
        newPos.y = y + Player.size / 2;
      }
    }
  }

  // -x -y
  if(x > 0 && y > 0 && map[x - 1 + (y - 1) * mapWidth])
  {
    if(newPos.x - x >= newPos.y - y)
    {
      if(newPos.x - Player.size / 2 < x)
      {
        newPos.x = x + Player.size / 2;
      }
    } else {
      if(newPos.y - Player.size / 2 < y)
      {
        newPos.y = y + Player.size / 2;
      }
    }
  }

  Player.pos = newPos;
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
      walk(vec2(0, deltaTime).rotate(Player.ang));
    }
    if(pKeystate[SDL_SCANCODE_DOWN])
    {
      walk(vec2(0, -deltaTime).rotate(Player.ang));
    }
    if(pKeystate[SDL_SCANCODE_RIGHT])
    {
      walk(vec2(deltaTime, 0).rotate(Player.ang));
    }
    if(pKeystate[SDL_SCANCODE_LEFT])
    {
      walk(vec2(-deltaTime, 0).rotate(Player.ang));
    }
    /*
    if(pKeystate[SDL_SCANCODE_RIGHT])
    {
      Player.ang -= deltaTime * PI;
    }
    if(pKeystate[SDL_SCANCODE_LEFT])
    {
      Player.ang += deltaTime * PI;
    }
    */

    surface = SDL_GetWindowSurface(window);

    render_background(surface);

    render_walls(surface);

    SDL_UpdateWindowSurface(window);
  }

  end_log();
}
