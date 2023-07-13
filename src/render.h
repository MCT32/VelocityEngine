#include <SDL2/SDL.h>
#include <string>
#include <map>

#include "util.h"
#include "player.h"
#include "config.h"
#include "logging.h"

extern player Player;

extern SDL_Color background_colors[];
extern std::string wall_textures[8];

void set_pixel(SDL_Surface* surface, int x, int y, SDL_Color color);

void render_background(SDL_Surface *surface);

void render_walls(SDL_Surface *surface);

void screenshot(SDL_Renderer *renderer);

void render_profiler(SDL_Surface* surface, double background, double walls, double ui);
