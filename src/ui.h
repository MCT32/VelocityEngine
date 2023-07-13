#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

extern TTF_Font* debug_font;

typedef struct {
  std::string name;
  void (*routine)();
} menuitem;

typedef struct menu_s {
  unsigned int itemCount;
  menuitem* items;
  struct menu_s* prevMenu;
  unsigned int selection;
} menu;

void render_text(SDL_Surface* surface, SDL_Color color, const std::string text, int x, int y);
void render_fps(SDL_Surface* surface, int fps);
void render_menu(SDL_Surface* surface, menu* currentMenu);
void render_ui(SDL_Surface* surface, int fps, bool paused, menu* currentMenu);
