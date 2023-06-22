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

void render_background(SDL_Renderer *renderer);

void render_walls(SDL_Renderer *renderer);

void screenshot(SDL_Renderer *renderer);
