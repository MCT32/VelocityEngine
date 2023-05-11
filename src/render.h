#include <SDL2/SDL.h>

#include "color.h"
#include "util.h"
#include "player.h"
#include "config.h"
#include "logging.h"

extern player Player;

extern color colors[];
extern color background_colors[];

void render_background(SDL_Renderer *renderer);

void render_walls(SDL_Renderer *renderer);

void screenshot(SDL_Renderer *renderer);
