#include "ui.h"

void render_text(SDL_Surface* surface, SDL_Color color, const std::string text, int x, int y)
{
  SDL_Surface* text_surface = TTF_RenderText_Solid(debug_font, text.c_str(), color);

  SDL_Rect dstrect = {x, y, text_surface->w, text_surface->h};
  SDL_BlitSurface(text_surface, NULL, surface, &dstrect);

  SDL_FreeSurface(text_surface);
}

void render_fps(SDL_Surface* surface, int fps)
{
  SDL_Color color = {255, 0, 0};
  render_text(surface, color, "FPS: " + std::to_string(fps), 0, 0);
}

void render_menu(SDL_Surface* surface, menu* currentMenu)
{
  SDL_Color color;

  for(int i = 0; i < currentMenu->itemCount; i++)
  {
    if(i == currentMenu->selection) color = {255, 255, 255}; else color = {255, 0, 0};

    render_text(surface, color, currentMenu->items[i].name, 0, 25 + 25 * i);
  }
}

void render_ui(SDL_Surface* surface, int fps, bool paused, menu* currentMenu)
{
  render_fps(surface, fps);

  if(paused) render_menu(surface, currentMenu);
}
