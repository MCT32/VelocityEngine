// Include external headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <map>
#include <chrono>

// Include custom headers
#include "vec2.h"
#include "util.h"
#include "gamestate.h"
#include "render.h"
#include "player.h"
#include "load.h"
#include "ui.h"
#include "logging.h"
#include "config.h"

// Global player struct
player Player;

// Textures
std::map<std::string, SDL_Surface*> textures;
std::string wall_textures[8];

// Backgound colors
SDL_Color background_colors[3];

TTF_Font* debug_font;

// Layout of the map
uint8_t *map;
uint8_t mapWidth, mapHeight;

void toggle_pause()
{
  gamestate.paused = !gamestate.paused;
  if(gamestate.paused)
  {
    SDL_SetRelativeMouseMode(SDL_FALSE);
  } else {
    SDL_SetRelativeMouseMode(SDL_TRUE);
  }
}

void quit()
{
  gamestate.quit = true;
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
  init_log();

  log(log_level::Info, "Setting up SDL");
  
  SDL_Window* window = NULL;
  SDL_Surface* surface = NULL;

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    log(log_level::Error, "Could not initialise SDL: " + std::string(SDL_GetError()));
    return 1;
  }

  TTF_Init();
  debug_font = TTF_OpenFont("arial.ttf", 25);
  if(!debug_font) log(log_level::Error, "Unable to load font");

  window = SDL_CreateWindow(
    "Velocity Engine",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
    680, 480,
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
  );

  if (window == NULL)
  {
    log(log_level::Error, "Could not create window: " + std::string(SDL_GetError()));
    return 1;
  }

  log(log_level::Info, "Finished setting up SDL");
  log(log_level::Info, "Loading map");

  if(!load_map(std::string("map/") + std::string(MAP_NAME)))
  {
    log(log_level::Error, "Unable to load map");
    return -1;
  }

  log(log_level::Info, "Finished loading map");

  SDL_Event event;
  gamestate.quit = false;
  gamestate.paused = false;

  bool profile = false;

  uint64_t NOW = SDL_GetPerformanceCounter();

  SDL_SetRelativeMouseMode(SDL_TRUE);

  menuitem pauseMenu[] =
  {
    {"resume", toggle_pause},
    {"options", toggle_pause},
    {"quit", quit}
  };

  menu pauseDef =
  {
    3,
    pauseMenu,
    NULL,
    0
  };

  menu* currentMenu = &pauseDef;

  while (!gamestate.quit)
  {
    uint64_t LAST = NOW;
    NOW = SDL_GetPerformanceCounter();

    double deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency()) / 1000;
    int fps = 1 / deltaTime;

    int relX = 0;
    int relY = 0;

    bool should_screenshot = false;

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT: gamestate.quit = true; break;
        case SDL_MOUSEMOTION: relX += event.motion.xrel; relY += event.motion.yrel;
        case SDL_KEYDOWN:
          switch (event.key.keysym.scancode)
	  {
	    case SDL_SCANCODE_ESCAPE:
	      gamestate.paused = !gamestate.paused;
	      if(gamestate.paused)
	      {
		SDL_SetRelativeMouseMode(SDL_FALSE);
	      } else {
		SDL_SetRelativeMouseMode(SDL_TRUE);
	      }
	      break;
	    case SDL_SCANCODE_F1:
	      gamestate.quit = true;
	      break;
	    case SDL_SCANCODE_F2:
	      should_screenshot = true;
	      break;
	    case SDL_SCANCODE_F3:
	      profile = !profile;
	      break;
	    case SDL_SCANCODE_DOWN:
	      if(gamestate.paused){
	        if(currentMenu->selection == currentMenu->itemCount - 1)
		{
		  currentMenu->selection = 0;
		} else {
		  currentMenu->selection++;
		}
	      }
	      break;
	    case SDL_SCANCODE_UP:
	      if(gamestate.paused){
	        if(currentMenu->selection == 0)
		{
		  currentMenu->selection = currentMenu->itemCount - 1;
		} else {
		  currentMenu->selection--;
		}
	      }
	      break;
	    case SDL_SCANCODE_RETURN:
	      if(gamestate.paused) (currentMenu->items[currentMenu->selection].routine)();
	      break;
	    default:
	      break;
	  }
      default:
        break;
      }
    }

    if(!gamestate.paused)
    {
      const uint8_t* pKeystate = SDL_GetKeyboardState(NULL);
      
      Player.processInput(pKeystate, deltaTime, relX);

      Player.update(deltaTime);
    }

    surface = SDL_GetWindowSurface(window);

    auto t1 = std::chrono::high_resolution_clock::now();
    render_background(surface);
    auto t2 = std::chrono::high_resolution_clock::now();
    render_walls(surface);
    auto t3 = std::chrono::high_resolution_clock::now();
    render_ui(surface, fps, gamestate.paused, currentMenu);
    auto t4 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> time_background = t2 - t1;
    std::chrono::duration<double, std::milli> time_walls = t3 - t2;
    std::chrono::duration<double, std::milli> time_ui = t4 - t3;

    if(profile) render_profiler(surface, time_background.count(), time_walls.count(), time_ui.count());
    
    //if(should_screenshot) screenshot(renderer);

    SDL_UpdateWindowSurface(window);
  }

  TTF_CloseFont(debug_font);

  TTF_Quit();
  SDL_Quit();

  end_log();
}
