// Include external headers
#include <SDL2/SDL.h>
#include <stdio.h>

// Include custom headers
#include "vec2.h"
#include "color.h"
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
  Function: main
  Purpose: Sets up windows and global variables and starts the game loop.

  Parameters:
    argc: Number of arguments.
    argv: Array of arguments.
  Returns: Exit code.
*/
int main(int argc, char* argv[])
{
  init_log();
  
  log_info("Initialising window... ");

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

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

  renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_RenderSetLogicalSize(renderer, 460, 320);

  log_info("Done\n");
  log_info("Loading map... ");

  load_map();

  log_info("Done\n");

  SDL_Event event;
  bool quit = false;
  bool paused = false;

  uint64_t NOW = SDL_GetPerformanceCounter();

  SDL_SetRelativeMouseMode(SDL_TRUE);

  while (!quit)
  {
    uint64_t LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    double deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency()) / 1000;

    int relX = 0;
    int relY = 0;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT: quit = true; break;
        case SDL_MOUSEMOTION: relX += event.motion.xrel; relY += event.motion.yrel;
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode)
	  {
	    case SDL_SCANCODE_ESCAPE:
	      paused = !paused;
	      if(paused)
	      {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	      } else {
		SDL_SetRelativeMouseMode(SDL_TRUE);
	      }
	      break;
	    case SDL_SCANCODE_F1:
	      quit = true;
	      break;
	    default:
	      break;
	  }
      default:
        break;
      }
    }

    if(!paused)
    {
      const uint8_t* pKeystate = SDL_GetKeyboardState(NULL);
      vec2 wishdir = vec2();
      if(pKeystate[SDL_SCANCODE_W])
      {
        wishdir = wishdir.add(vec2(0, 1).rotate(Player.getRotation()));
      }
      if(pKeystate[SDL_SCANCODE_S])
      {
        wishdir = wishdir.add(vec2(0, -1).rotate(Player.getRotation()));
      }
      if(pKeystate[SDL_SCANCODE_D])
      {
        wishdir = wishdir.add(vec2(1, 0).rotate(Player.getRotation()));
      }
      if(pKeystate[SDL_SCANCODE_A])
      {
        wishdir = wishdir.add(vec2(-1, 0).rotate(Player.getRotation()));
      }

      Player.setVelocity(wishdir.normalize());
      Player.update(deltaTime);

      Player.rotate(- float(relX) / 180 * SENSITIVITY);
    }

    SDL_RenderClear(renderer);

    render_background(renderer);

    render_walls(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);
  }

  end_log();
}
