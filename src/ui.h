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

void render_text(SDL_Renderer* renderer, SDL_Color color, std::string text, int x, int y);
void render_fps(SDL_Renderer* renderer, int fps);
void render_menu(SDL_Renderer* renderer, menu* currentMenu);
void render_ui(SDL_Renderer* renderer, int fps, bool paused, menu* currentMenu);
