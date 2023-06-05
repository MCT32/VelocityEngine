#include "ui.h"

void render_text(SDL_Renderer* renderer, SDL_Color color, std::string text, int x, int y)
{
  SDL_Surface* surface = TTF_RenderText_Solid(debug_font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect dstrect = {x, y, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &dstrect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void render_fps(SDL_Renderer* renderer, int fps)
{
  SDL_Color color = {255, 0, 0};
  render_text(renderer, color, "FPS: " + std::to_string(fps), 0, 0);
}

void render_menu(SDL_Renderer* renderer, menu* currentMenu)
{
  SDL_Color color;

  for(int i = 0; i < currentMenu->itemCount; i++)
  {
    if(i == currentMenu->selection) color = {255, 255, 255}; else color = {255, 0, 0};

    render_text(renderer, color, currentMenu->items[i].name, 0, 25 + 25 * i);
  }
}

void render_ui(SDL_Renderer* renderer, int fps, bool paused, menu* currentMenu)
{
  render_fps(renderer, fps);

  if(paused) render_menu(renderer, currentMenu);
}
