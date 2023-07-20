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


// Global font
TTF_Font* debug_font;


// Surface used to cache background
SDL_Surface* background_cache;


// Layout of the map
uint8_t *map;
uint8_t mapWidth, mapHeight;


/*
  Function: toggle_pause
  Purpose: Toggles between the paused and unpaused state.

  Parameters: None
  Returns: Nothing
*/
void toggle_pause()
{
  gamestate.paused = !gamestate.paused;		// Toggle paused boolean
  if(gamestate.paused)				// If game was just paused...
  {
    SDL_SetRelativeMouseMode(SDL_FALSE);	// Allow mouse of of window
  } else {					// If game was just unpaused...
    SDL_SetRelativeMouseMode(SDL_TRUE);		// Contrain mouse to inside window
  }
}


/*
  Function: quit
  Purpose: Marks the game to quit.

  Parameters: None
  Returns: Nothing
*/
void quit()
{
  gamestate.quit = true;	// Set quit boolean to true so it can be checked at the end of the game loop
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
  // Start logging
  init_log();
  log(log_level::Info, "Setting up SDL");


  // Declare window and surface to be initiated later  
  SDL_Window* window = NULL;
  SDL_Surface* surface = NULL;


  // SDL initialising and error checking
  if (SDL_Init(SDL_INIT_VIDEO) < 0)							// If SDL failed to initialise
  {
    log(log_level::Error, "Could not initialise SDL: " + std::string(SDL_GetError()));	// Log error
    return 1;										// Return error code and quit the program
  }


  // Setup fonts
  TTF_Init();							// Initialise font library
  debug_font = TTF_OpenFont("arial.ttf", 25);			// Load font used for debugging
  if(!debug_font) log(log_level::Error, "Unable to load font");	// Check font loaded successfully and if not log error


  // Set up window
  window = SDL_CreateWindow(				// Create window
    "Velocity Engine",					// Set window title
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,	// Leave initial window position undefined
    680, 480,						// Set size of window
    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE		// Make window visable and resizable
  );

  if (window == NULL)									// If window was not created...
  {
    log(log_level::Error, "Could not create window: " + std::string(SDL_GetError()));	// Log error
    return 1;										// Return error code and quit program
  }


  // Log completion of SDL initialisation
  log(log_level::Info, "Finished setting up SDL");


  // Log beginning of map loading
  log(log_level::Info, "Loading map");


  // Map loading
  if(!load_map(std::string("map/") + std::string(MAP_NAME)))	// Try loading map, if map fails to load...
  {
    log(log_level::Error, "Unable to load map");		// Log error
    return -1;							// Return error code and quit program
  }


  // Log end of map loading
  log(log_level::Info, "Finished loading map");


  // Initialise variables
  SDL_Event event;				// Buffer for event checking

  gamestate.quit = false;			// Set quit to false so game doesnt immediately end
  gamestate.paused = false;			// Start the game unpaused

  bool profile = false;				// Turn profiler off by default

  uint64_t NOW = SDL_GetPerformanceCounter();	// Initialise first timestamp for delta time calculation


  // Record relative mouse movement instead of absolute
  SDL_SetRelativeMouseMode(SDL_TRUE);


  // Menu definitions
  menuitem pauseMenu[] =	// Items in pause menu
  {
    {"resume", toggle_pause},	// Resume, toggles pause when pressed
    {"options", toggle_pause},	// Options, toggles pause when pressed (TODO: Add options menu)
    {"quit", quit}		// Quit, sets quit boolean when pressed
  };

  menu pauseDef =		// Pause menu definition
  {
    3,				// 3 menu items
    pauseMenu,			// Item list
    NULL,			// No previous menu
    0				// First item selected
  };


  // Set pause menu to current menu
  menu* currentMenu = &pauseDef;


  // Keep resolution to check for resizing
  int old_res[2] = {0, 0};


  // Main game loop
  while (!gamestate.quit) // Check if game should be closed
  {
    // Delta time calculations
    uint64_t LAST = NOW;		// Move last timestamp
    NOW = SDL_GetPerformanceCounter();	// Record new timestamp

    double deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency()) / 1000;	// Calculate time since last
													// frame in seconds
    int fps = 1 / deltaTime;		// Calculate framerate from delta time


    // Initialise variables to keep mouse movement
    int relX = 0;
    int relY = 0;


    // Initialise variable for if a screenshot should be taken
    bool should_screenshot = false;


    // Check events
    while (SDL_PollEvent(&event)) // Iterate events in queue until there are no more
    {
      // Check event type
      switch (event.type)
      {
	// Quit event
	case SDL_QUIT: gamestate.quit = true; break; // Mark game to be quit
	
	
	// Mouse movement event
        case SDL_MOUSEMOTION: relX += event.motion.xrel; relY += event.motion.yrel; // Record mouse movement into variables
										    // for use later

	// Keypress event
        case SDL_KEYDOWN:
	  // Check which button is pressed
          switch (event.key.keysym.scancode)
	  {
	    // Escape pressed
	    case SDL_SCANCODE_ESCAPE:
	      toggle_pause();
	      break;


	    // F1 pressed
	    case SDL_SCANCODE_F1:
	      gamestate.quit = true; // Quit game
	      break;


	    // F2 pressed
	    case SDL_SCANCODE_F2:
	      should_screenshot = true; // Take screenshot
	      break;


	    // F3 pressed
	    case SDL_SCANCODE_F3:
	      profile = !profile; // Toggle profiler
	      break;


	    // Menu navigation
	    case SDL_SCANCODE_DOWN: // Down pressed
	      if(gamestate.paused){						// If game is paused...
	        if(currentMenu->selection == currentMenu->itemCount - 1)	// If last item is selected...
		{
		  currentMenu->selection = 0;					// Wrap around to the beginning
		} else {							// Otherwise...
		  currentMenu->selection++;					// Move selection down
		}
	      }
	      break;
	    case SDL_SCANCODE_UP: // Up pressed
	      if(gamestate.paused){						// If game is paused...
	        if(currentMenu->selection == 0)					// If first item is selected...
		{
		  currentMenu->selection = currentMenu->itemCount - 1;		// Wrap around to the end
		} else {							// Otherwise...
		  currentMenu->selection--;					// Move selection up
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


    // Run game logic
    if(!gamestate.paused)					// Check if game is paused
    {
      const uint8_t* pKeystate = SDL_GetKeyboardState(NULL);	// Get keyboard state
      
      Player.processInput(pKeystate, deltaTime, relX);		// Process player inputs

      Player.update(deltaTime);					// Update player
    }


    // Rendering
    surface = SDL_GetWindowSurface(window); // Get window surface for rendering

    if(surface->w != old_res[0] || surface->h != old_res[1])	// If resolution has changed...
    {
      // Store new resolution
      old_res[0] = surface->w;
      old_res[1] = surface->h;

      // Rerender background
      background_cache = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0, 0, 0, 0);
      render_background(background_cache);
    }


    // Render to screen while profiling
    auto t1 = std::chrono::high_resolution_clock::now();	// Record first timestamp
    SDL_BlitSurface(background_cache, NULL, surface, NULL);	// Blit background
    auto t2 = std::chrono::high_resolution_clock::now();	// Record second timestamp
    render_walls(surface);					// Render walls
    auto t3 = std::chrono::high_resolution_clock::now();	// Record third timestamp
    render_ui(surface, fps, gamestate.paused, currentMenu);	// Render ui
    auto t4 = std::chrono::high_resolution_clock::now();	// Record fourth timestamp

    // Calculate time for each step using timestamps
    std::chrono::duration<double, std::milli> time_background = t2 - t1;
    std::chrono::duration<double, std::milli> time_walls = t3 - t2;
    std::chrono::duration<double, std::milli> time_ui = t4 - t3;


    // Render profiler
    if(profile) render_profiler(surface, time_background.count(), time_walls.count(), time_ui.count());
    

    // Take screenshot
    if(should_screenshot) screenshot(surface);


    // Render to screen
    SDL_UpdateWindowSurface(window);
  }


  // Remove font
  TTF_CloseFont(debug_font);


  // Deinitialise libraries
  TTF_Quit();
  SDL_Quit();


  // Deinitialise log
  end_log();
}
