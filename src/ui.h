#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

extern TTF_Font* debug_font;

void render_fps(SDL_Renderer* renderer, int fps);
void render_ui(SDL_Renderer* renderer, int fps);
